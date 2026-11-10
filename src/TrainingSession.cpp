#include <random>    // For a random number generator
#include <algorithm> // For std::shuffle, std::find
#include <stdexcept>
#include <cctype>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include "TrainingSession.h"

namespace {

std::string TrimSpaces(const std::string& str) {
    std::size_t begin = 0;
    std::size_t end = str.size();
    while (begin < end && std::isspace(static_cast<unsigned char>(str[begin])))
        begin++;
    while (end > begin && std::isspace(static_cast<unsigned char>(str[end - 1])))
        end--;
    return str.substr(begin, end - begin);
}

}

std::vector<int> ParseIdList(const std::string& line) {
    std::vector<int> result;
    std::string number;

    for (std::size_t i = 0; i <= line.size(); i++) {
        if (i < line.size() && std::isdigit(static_cast<unsigned char>(line[i]))) {
            number += line[i];
        }
        else
            if (!number.empty()) {
                if (number.size() <= 9) // Protection against overflow
                    result.push_back(std::stoi(number));
                number.clear();
            }
    }
    return result;
}

std::vector<std::shared_ptr<IQuestion>> FilterQuestions(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings) {
    std::vector<std::shared_ptr<IQuestion>> result;
    const auto& ids = settings.category_ids;

    for (const auto& q : all_questions) {
        bool category_ok = ids.empty() || std::find(ids.begin(), ids.end(), q->GetCategoryId()) != ids.end();
        bool cost_ok = q->GetCost() >= settings.min_cost && q->GetCost() <= settings.max_cost;
        if (category_ok && cost_ok)
            result.push_back(q);
    }
    return result;
}

void TrainingSession::Generate(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings) {
    if (settings.min_cost > settings.max_cost)
        throw std::invalid_argument("Минимальная стоимость вопроса больше максимальной.");
    if (settings.question_count <= 0)
        throw std::invalid_argument("Количество вопросов должно быть больше нуля.");

    auto suitable = FilterQuestions(all_questions, settings);
    if (suitable.empty())
        throw std::runtime_error("Нет вопросов, подходящих под выбранные параметры.");

    std::random_device rd;
    std::mt19937 g(rd());

    std::map<int, std::vector<std::shared_ptr<IQuestion>>> by_category;
    for (const auto& q : suitable)
        by_category[q->GetCategoryId()].push_back(q);

    std::vector<std::vector<std::shared_ptr<IQuestion>>> groups;
    for (auto& item : by_category) {
        std::shuffle(item.second.begin(), item.second.end(), g);
        groups.push_back(item.second);
    }
    std::shuffle(groups.begin(), groups.end(), g);

    std::size_t need = std::min(static_cast<std::size_t>(settings.question_count), suitable.size());
    std::vector<std::shared_ptr<IQuestion>> selected;

    for (std::size_t round = 0; selected.size() < need; round++) {
        for (const auto& group : groups) {
            if (round < group.size() && selected.size() < need)
                selected.push_back(group[round]);
        }
    }
    std::shuffle(selected.begin(), selected.end(), g);

    LoadQuestions(selected);
}

void TrainingSession::LoadQuestions(const std::vector<std::shared_ptr<IQuestion>>& prepared_questions) {
    Reset();
    questions = prepared_questions;
}

bool TrainingSession::IsFinished() const {
    return current_index >= questions.size();
}

std::shared_ptr<IQuestion> TrainingSession::GetCurrentQuestion() const {
    if (IsFinished())
        throw std::out_of_range("Тренировка завершена.");
    return questions[current_index];
}

int TrainingSession::GetCurrentNumber() const {
    return static_cast<int>(current_index) + 1;
}

int TrainingSession::GetQuestionCount() const {
    return static_cast<int>(questions.size());
}

bool TrainingSession::SubmitAnswer(const std::string& user_input) {
    auto question = GetCurrentQuestion();
    std::string answer = TrimSpaces(user_input);

    bool is_correct = !answer.empty() && question->CheckAnswer(answer);

    history.push_back({ question, answer, is_correct });
    statistics.AddResult(question->GetCategoryId(), question->GetCost(), is_correct);
    current_index++;

    return is_correct;
}

const Statistics& TrainingSession::GetStatistics() const {
    return statistics;
}

const std::vector<AnswerRecord>& TrainingSession::GetHistory() const {
    return history;
}

std::vector<std::shared_ptr<IQuestion>> TrainingSession::GetMistakes() const {
    std::vector<std::shared_ptr<IQuestion>> mistakes;
    for (const auto& record : history) {
        if (!record.is_correct)
            mistakes.push_back(record.question);
    }
    return mistakes;
}

TrainingSession TrainingSession::CreateMistakesReview() const {
    TrainingSession review;
    review.LoadQuestions(GetMistakes());
    return review;
}

void TrainingSession::Reset() {
    questions.clear();
    current_index = 0;
    history.clear();
    statistics = Statistics();
}
