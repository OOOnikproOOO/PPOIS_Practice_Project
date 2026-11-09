#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <stdexcept>
#include <algorithm> // For std::find

#if defined(_WIN32)
#define NOMINMAX // Prevents min/max macros from windows.h breaking std::numeric_limits
#include <windows.h> // Connect Windows tools
#endif

#include "Database.h"
#include "GameSession.h"
#include "ImageQuestion.h"
#include "AudioQuestion.h"
#include "AssetsWork.h"
#include "TrainingSession.h"
#include "Statistics.h"
#include "RecommendationSystem.h"
#include "GameLogger.h"

using namespace std;

int ReadNumber(const string& prompt, int min_value, int max_value) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line))
            throw runtime_error("Ввод прерван.");

        try {
            size_t pos = 0;
            int value = stoi(line, &pos);
            bool only_spaces_after = line.find_first_not_of(" \t\r", pos) == string::npos;
            if (only_spaces_after && value >= min_value && value <= max_value)
                return value;
        }
        catch (const exception&) {
        }
        cout << "Введите целое число от " << min_value << " до " << max_value << "." << endl;
    }
}

void PresentQuestion(const shared_ptr<IQuestion>& question) {
    cout << question->GetText() << endl;

    if (auto img_q = dynamic_pointer_cast<ImageQuestion>(question)) {
        cout << "[>>> Открытие изображения <<<]" << endl;
        OpenImageInViewer(img_q->GetImagePath());
    }
    else
        if (auto aud_q = dynamic_pointer_cast<AudioQuestion>(question)) {
            cout << "[>>> Воспроизведение аудио <<<]" << endl;
            PlayAudioBackground(aud_q->GetAudioPath());
        }
}

// Number of characters as seen in the console (UTF-8: Cyrillic letters take 2 bytes, but 1 position)
size_t GetDisplayLength(const string& text) {
    size_t length = 0;
    for (unsigned char ch : text) {
        if ((ch & 0xC0) != 0x80) // Skip continuation bytes of multi-byte characters
            length++;
    }
    return length;
}

string Repeat(const string& piece, size_t count) {
    string result;
    for (size_t i = 0; i < count; i++)
        result += piece;
    return result;
}

string GetCategoryName(int category_id, const DataManager<Category>& cat_manager) {
    try {
        return cat_manager.GetById(category_id)->GetName();
    }
    catch (const runtime_error&) {
        return "Тема №" + to_string(category_id);
    }
}

void LogOrWarn(bool written, const GameLogger& logger) {
    if (!written)
        cout << "⚠ Не удалось записать историю игры в файл " << logger.GetFilePath() << endl;
}

string ReadUserName() {
    string line;
    cout << "Введите ваше имя >>> ";
    if (!getline(cin, line))
        throw runtime_error("Ввод прерван.");
    return GameLogger::NormalizeUserName(line);
}

// ============================================================
// Classic game
// ============================================================

void RunClassicGame(const DataManager<Category>& cat_manager, const DataManager<IQuestion>& q_manager,
    GameLogger& logger, const string& user_name) {
    GameSession session;
    string user_answer;

    while (true) {
        cout << "\n=======================================" << endl;
        cout << " ВАШ СЧЕТ: " << session.GetScore() << endl;
        cout << "=======================================" << endl;
        cout << endl << "Выберите Тему и введите её ID: " << endl;

        auto categories = cat_manager.GetAll();
        auto all_questions = q_manager.GetAll();

        int max_cat_id = 0;
        for (const auto& cat : categories) {
            if (cat->GetId() > max_cat_id)
                max_cat_id = cat->GetId();

            bool has_active_questions = false;
            for (const auto& question_item : all_questions) {
                if (question_item->GetCategoryId() == cat->GetId() && !session.IsQuestionPlayed(question_item->GetId())) {
                    has_active_questions = true;
                    break;
                }
            }

            if (has_active_questions)
                cout << cat->GetId() << ". " << cat->GetName() << endl;
        }
        cout << "0. Выйти в главное меню" << endl;

        int cat_id = ReadNumber("\nВаш выбор >>> ", 0, max_cat_id);

        if (cat_id == 0) {
            cout << "\nИгра окончена! Итоговый счет: " << session.GetScore() << endl;
            cout << "Возврат в главное меню..." << endl;
            LogOrWarn(logger.LogClassicGame(user_name, session.GetScore(), session.GetCorrectCount(), session.GetIncorrectCount()), logger);
            break;
        }

        cout << "\nДоступные вопросы:" << endl;
        auto questions = q_manager.GetAll();
        bool found = false;
        int min_cost = numeric_limits<int>::max();
        int max_cost = 0;

        for (const auto& q : questions) {
            if (q->GetCategoryId() == cat_id && !session.IsQuestionPlayed(q->GetId())) {
                cout << "| " << q->GetCost() << " очков" << endl;
                found = true;
                if (q->GetCost() < min_cost)
                    min_cost = q->GetCost();
                if (q->GetCost() > max_cost)
                    max_cost = q->GetCost();
            }
        }

        if (!found) {
            cout << "В этой категории больше нет несыгранных вопросов!" << endl;
            continue;
        }

        int cost = ReadNumber("\nВведите цену вопроса: ", min_cost, max_cost);

        shared_ptr<IQuestion> selected_q = nullptr;
        for (const auto& q : questions) {
            if (q->GetCategoryId() == cat_id && q->GetCost() == cost && !session.IsQuestionPlayed(q->GetId())) {
                selected_q = q;
                break;
            }
        }

        if (selected_q) {
            cout << "\nВнимание! Вопрос:" << endl;
            PresentQuestion(selected_q);

            cout << "\nВаш ответ >>> ";
            getline(cin, user_answer);

            StopAudioBackground();

            if (user_answer.empty()) {
                cout << "\n⏭ Вопрос пропущен! Правильный ответ: " << selected_q->GetPrimaryAnswer() << endl;
                session.ProcessResult(0, false, selected_q->GetId());
            }
            else {
                bool is_correct = selected_q->CheckAnswer(user_answer);
                session.ProcessResult(selected_q->GetCost(), is_correct, selected_q->GetId());

                if (is_correct)
                    cout << "\n✅ ПРАВИЛЬНО! Вы заработали " << selected_q->GetCost() << " очков." << endl;
                else {
                    cout << "\n❌ НЕВЕРНО! Вы потеряли " << selected_q->GetCost() << " очков." << endl;
                    cout << "Правильный ответ: " << selected_q->GetPrimaryAnswer() << endl;
                }
            }
        }
        else
            cout << "Вопрос с такой ценой не найден или уже сыгран." << endl;
    }
}

// ============================================================
// Training mode
// ============================================================

vector<int> ReadTrainingCategories(const DataManager<Category>& cat_manager, const DataManager<IQuestion>& q_manager) {
    cout << "\nДоступные темы:" << endl;
    for (const auto& cat : cat_manager.GetAll()) {
        int count = 0;
        for (const auto& q : q_manager.GetAll()) {
            if (q->GetCategoryId() == cat->GetId())
                count++;
        }
        cout << cat->GetId() << ". " << cat->GetName() << " (" << count << " вопр.)" << endl;
    }

    string line;
    while (true) {
        cout << "\nВведите ID тем (0 — смешанная тренировка по всем темам) >>> ";
        if (!getline(cin, line))
            throw runtime_error("Ввод прерван.");

        vector<int> ids = ParseIdList(line);
        if (ids.empty()) {
            cout << "Не указано ни одной темы." << endl;
            continue;
        }

        vector<int> result;
        bool all_topics = false;
        bool all_valid = true;

        for (int id : ids) {
            if (id == 0) {
                all_topics = true;
                break;
            }
            try {
                cat_manager.GetById(id);
            }
            catch (const runtime_error&) {
                cout << "Темы с ID " << id << " не существует." << endl;
                all_valid = false;
                break;
            }
            if (find(result.begin(), result.end(), id) == result.end())
                result.push_back(id);
        }

        if (all_topics)
            return {};
        if (all_valid)
            return result;
    }
}


string ProgressBar(int percent) {
    const int width = 10;
    int filled = (percent * width + 50) / 100;
    string bar = "[";
    for (int i = 0; i < width; i++)
        bar += (i < filled) ? "█" : "░";
    return bar + "]";
}

// Command that ends the training before the last question
bool IsExitCommand(const string& input) {
    string command = input;
    size_t begin = command.find_first_not_of(" \t\r");
    size_t end = command.find_last_not_of(" \t\r");
    command = (begin == string::npos) ? "" : command.substr(begin, end - begin + 1);
    return command == "/выход" || command == "/exit";
}

void PrintStatLine(const string& title, const StatEntry& entry) {
    cout << "  " << ProgressBar(entry.GetPercent()) << " " << title << " — "
        << entry.correct << " из " << entry.total << ", " << entry.GetPercent() << "%" << endl;
}

// Returns true if the user left the training before the last question
bool PlayTraining(TrainingSession& session, const DataManager<Category>& cat_manager) {
    string user_answer;

    while (!session.IsFinished()) {
        auto question = session.GetCurrentQuestion();

        string header = " Вопрос " + to_string(session.GetCurrentNumber()) + " из " + to_string(session.GetQuestionCount())
            + " | " + GetCategoryName(question->GetCategoryId(), cat_manager)
            + " | " + to_string(question->GetCost()) + " баллов ";
        string line = Repeat("-", GetDisplayLength(header));

        cout << "\n" << line << endl;
        cout << header << endl;
        cout << line << endl;
        PresentQuestion(question);

        cout << "\nВаш ответ (Enter — пропустить, /выход — завершить тренировку) >>> ";
        if (!getline(cin, user_answer))
            user_answer.clear();

        StopAudioBackground();

        if (IsExitCommand(user_answer)) {
            session.Abort();
            cout << "\nТренировка завершена досрочно." << endl;
            return true;
        }

        bool is_correct = session.SubmitAnswer(user_answer);
        const auto& record = session.GetHistory().back();

        if (is_correct)
            cout << "\n✅ ПРАВИЛЬНО!" << endl;
        else
            if (record.user_answer.empty())
                cout << "\n⏭ Вопрос пропущен. Правильный ответ: " << question->GetPrimaryAnswer() << endl;
            else
                cout << "\n❌ НЕВЕРНО! Правильный ответ: " << question->GetPrimaryAnswer() << endl;

        if (!cin)
            throw runtime_error("Ввод прерван.");
    }
    return false;
}

void PrintTrainingResults(const TrainingSession& session, const DataManager<Category>& cat_manager,
    const RecommendationSystem& recommender, const string& title, bool show_recommendation) {
    const Statistics& stats = session.GetStatistics();

    cout << "\n=======================================" << endl;
    cout << " " << title << endl;
    cout << "=======================================" << endl;

    PrintStatLine("Всего", stats.GetTotal());

    cout << "\nПо темам:" << endl;
    for (const auto& item : stats.GetCategoryStats())
        PrintStatLine(GetCategoryName(item.first, cat_manager), item.second);

    cout << "\nПо сложности:" << endl;
    for (const auto& item : stats.GetDifficultyStats())
        PrintStatLine(item.first, item.second);

    if (show_recommendation) {
        Recommendation rec = recommender.Analyze(stats);
        cout << "\n💡 " << recommender.BuildText(rec, cat_manager) << endl;
    }
}

// Asks for a difficulty level taken from the questions themselves; returns "" for "any"
string ReadTrainingDifficulty(const DataManager<IQuestion>& q_manager) {
    vector<string> levels;
    for (const auto& q : q_manager.GetAll()) {
        if (!q->GetDifficulty().empty() && find(levels.begin(), levels.end(), q->GetDifficulty()) == levels.end())
            levels.push_back(q->GetDifficulty());
    }
    sort(levels.begin(), levels.end());

    cout << "\nУровень сложности вопросов:" << endl;
    cout << "0. Любой" << endl;
    for (size_t i = 0; i < levels.size(); i++)
        cout << i + 1 << ". " << levels[i] << endl;

    int choice = ReadNumber("\nВаш выбор >>> ", 0, static_cast<int>(levels.size()));
    return choice == 0 ? "" : levels[choice - 1];
}

// Prints the results and writes them to the history log; does nothing if no question was answered
void FinishTraining(const TrainingSession& session, bool aborted, const DataManager<Category>& cat_manager,
    const RecommendationSystem& recommender, const string& title, bool show_recommendation,
    GameLogger& logger, const string& user_name) {
    if (session.GetStatistics().IsEmpty()) {
        cout << "\nНи на один вопрос не было дано ответа — результатов нет." << endl;
        return;
    }
    PrintTrainingResults(session, cat_manager, recommender, aborted ? title + " (ДОСРОЧНО)" : title, show_recommendation);
    LogOrWarn(logger.LogTraining(user_name, show_recommendation ? "Тренировка" : "Работа над ошибками", session.GetStatistics(), aborted), logger);
}

void RunTraining(const DataManager<Category>& cat_manager, const DataManager<IQuestion>& q_manager,
    GameLogger& logger, const string& user_name) {
    cout << "\n=======================================" << endl;
    cout << " РЕЖИМ \"ТРЕНИРОВКА\"" << endl;
    cout << "=======================================" << endl;
    cout << "1. Начать настройку тренировки" << endl;
    cout << "0. Вернуться в главное меню" << endl;
    if (ReadNumber("\nВаш выбор >>> ", 0, 1) == 0)
        return;

    TrainingSettings settings;
    settings.category_ids = ReadTrainingCategories(cat_manager, q_manager);
    settings.difficulty = ReadTrainingDifficulty(q_manager);

    int available = static_cast<int>(FilterQuestions(q_manager.GetAll(), settings).size());
    if (available == 0) {
        cout << "\nПод выбранные параметры не подходит ни один вопрос." << endl;
        return;
    }
    if (available == 1) {
        cout << "Под выбранные параметры подходит только 1 вопрос — начинаем!" << endl;
        settings.question_count = 1;
    }
    else
        settings.question_count = ReadNumber("Количество вопросов (1–" + to_string(available) + ") >>> ", 1, available);

    TrainingSession session;
    session.Generate(q_manager.GetAll(), settings);

    RecommendationSystem recommender;
    bool aborted = PlayTraining(session, cat_manager);
    FinishTraining(session, aborted, cat_manager, recommender, "ИТОГИ ТРЕНИРОВКИ", true, logger, user_name);
    if (aborted)
        return;

    // "Repeat mistakes"
    while (true) {
        int mistakes = static_cast<int>(session.GetMistakes().size());
        if (mistakes == 0) {
            cout << "\n🏆 Ошибок нет — повторять нечего!" << endl;
            return;
        }

        cout << "\n1. Повторить ошибки (" << mistakes << " вопросов)" << endl;
        cout << "0. Вернуться в главное меню" << endl;
        if (ReadNumber("\nВаш выбор >>> ", 0, 1) == 0)
            return;

        session = session.CreateMistakesReview();
        aborted = PlayTraining(session, cat_manager);
        FinishTraining(session, aborted, cat_manager, recommender, "ИТОГИ РАБОТЫ НАД ОШИБКАМИ", false, logger, user_name);
        if (aborted)
            return;
    }
}

// Entry point
int main() {
#if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try {
        Database db("game_data.db");
        db.Initialize();

        DataManager<Category> cat_manager;
        DataManager<IQuestion> q_manager;

        db.LoadCategories(cat_manager);
        db.LoadQuestions(q_manager);

        GameLogger logger;
        string user_name = ReadUserName();
        cout << "Привет, " << user_name << "!" << endl;

        while (true) {
            cout << "\n=======================================" << endl;
            cout << " СВОЯ ИГРА — ГЛАВНОЕ МЕНЮ" << endl;
            cout << "=======================================" << endl;
            cout << "1. Режим \"Классическая игра\"" << endl;
            cout << "2. Режим \"Тренировка\"" << endl;
            cout << "0. Выход" << endl;

            int choice = ReadNumber("\nВаш выбор >>> ", 0, 2);

            if (choice == 0)
                break;
            if (choice == 1)
                RunClassicGame(cat_manager, q_manager, logger, user_name);
            else
                RunTraining(cat_manager, q_manager, logger, user_name);
        }
    }
    catch (const std::exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
    }

    return 0;
}