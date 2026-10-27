#include <iostream>
#include <windows.h> // Connect Windows tools
#include <string>
#include "Database.h"
#include "GameSession.h"
#include "ImageQuestion.h"
#include "AudioQuestion.h"
#include "AssetsWork.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        Database db("game_data.db");
        db.Initialize();

        DataManager<Category> cat_manager;
        DataManager<IQuestion> q_manager;

        db.LoadCategories(cat_manager);
        db.LoadQuestions(q_manager);

        GameSession session;
        string user_answer;

        while (true) {
            cout << "\n=======================================" << endl;
            cout << " ВАШ СЧЕТ: " << session.GetScore() << endl;
            cout << "=======================================" << endl;
            cout << endl << "Выберите Тему и введите её ID (или 0 для выхода): " << endl;

            auto categories = cat_manager.GetAll();
            auto all_questions = q_manager.GetAll();

            for (const auto& cat : categories) {
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

            int cat_id;
            cout << "\nВаш выбор >>> ";
            cin >> cat_id;

            if (cat_id == 0) {
                cout << "\nИгра окончена! Итоговый счет: " << session.GetScore() << endl;
                break;
            }

            cout << "\nДоступные вопросы:" << endl;
            auto questions = q_manager.GetAll();
            bool found = false;

            for (const auto& q : questions) {
                if (q->GetCategoryId() == cat_id && !session.IsQuestionPlayed(q->GetId())) {
                    cout << "| " << q->GetCost() << " очков" << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "В этой категории больше нет несыгранных вопросов!" << endl;
                continue;
            }

            int cost;
            cout << "\nВведите цену вопроса: ";
            cin >> cost;
            cin.ignore();

            shared_ptr<IQuestion> selected_q = nullptr;
            for (const auto& q : questions) {
                if (q->GetCategoryId() == cat_id && q->GetCost() == cost && !session.IsQuestionPlayed(q->GetId())) {
                    selected_q = q;
                    break;
                }
            }

            if (selected_q) {
                cout << "\nВнимание! Вопрос:" << endl;
                cout << selected_q->GetText() << endl;
                
                if (auto img_q = dynamic_pointer_cast<ImageQuestion>(selected_q)) {
                    cout << "[>>> Открытие изображения <<<]" << endl;
                    OpenImageInViewer(img_q->GetImagePath());
                }
                else 
                    if (auto aud_q = dynamic_pointer_cast<AudioQuestion>(selected_q)) {
                        cout << "[>>> Воспроизведение аудио <<<]" << endl;
                        PlayAudioBackground(aud_q->GetAudioPath());
                    }
                
                cout << "\nВаш ответ >>> ";
                getline(cin, user_answer);

                StopAudioBackground();

                if (user_answer.empty()) {
                    cout << "\nВопрос пропущен! Правильный ответ: " << selected_q->GetPrimaryAnswer() << endl;
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
    catch (const std::exception& e) {
        cerr << "Критическая ошибка: " << e.what() << endl;
    }

    return 0;
}