#ifndef TRAININGSESSION_H
#define TRAININGSESSION_H

#include <vector>
#include <memory>
#include <string>
#include "IQuestion.h"
#include "Statistics.h"

struct TrainingSettings {
    std::vector<int> category_ids; // Empty list means "all categories" (mixed training)
    int min_cost = 100;
    int max_cost = 500;
    int question_count = 10;
};

// One answered question
struct AnswerRecord {
    std::shared_ptr<IQuestion> question;
    std::string user_answer;
    bool is_correct = false;
};

std::vector<int> ParseIdList(const std::string& line);

// All questions that match the selected categories and cost range
std::vector<std::shared_ptr<IQuestion>> FilterQuestions(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings);

class TrainingSession {
public:
    void Generate(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings);

    void LoadQuestions(const std::vector<std::shared_ptr<IQuestion>>& prepared_questions);

    bool IsFinished() const;

    std::shared_ptr<IQuestion> GetCurrentQuestion() const;

    int GetCurrentNumber() const;

    int GetQuestionCount() const;

    // An empty answer counts as a mistake
    bool SubmitAnswer(const std::string& user_input);

    const Statistics& GetStatistics() const;

    const std::vector<AnswerRecord>& GetHistory() const;

    std::vector<std::shared_ptr<IQuestion>> GetMistakes() const;

    TrainingSession CreateMistakesReview() const;

private:
    void Reset();
    std::vector<std::shared_ptr<IQuestion>> questions;
    std::size_t current_index = 0;
    std::vector<AnswerRecord> history;
    Statistics statistics;
};

#endif
