#ifndef TRAININGSESSION_H
#define TRAININGSESSION_H

#include <vector>
#include <memory>
#include <string>
#include "IQuestion.h"
#include "Statistics.h"

// Parameters chosen by the user before the training starts
struct TrainingSettings {
    std::vector<int> category_ids; // Empty list means "all categories" (mixed training)
    int min_cost = 100;
    int max_cost = 500;
    int question_count = 10;
};

// One answered question of the training
struct AnswerRecord {
    std::shared_ptr<IQuestion> question;
    std::string user_answer;
    bool is_correct = false;
};

// Parses a line like "1 5, 12" into a list of numbers, ignoring everything that is not a number
std::vector<int> ParseIdList(const std::string& line);

// Returns all questions that match the selected categories and cost range
std::vector<std::shared_ptr<IQuestion>> FilterQuestions(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings);

class TrainingSession {
public:
    // Selects random questions according to the settings (evenly across the chosen categories)
    void Generate(const std::vector<std::shared_ptr<IQuestion>>& all_questions, const TrainingSettings& settings);

    // Starts a training on a ready-made list of questions (used for "repeat mistakes")
    void LoadQuestions(const std::vector<std::shared_ptr<IQuestion>>& prepared_questions);

    bool IsFinished() const;

    std::shared_ptr<IQuestion> GetCurrentQuestion() const;

    // Number of the current question starting from 1
    int GetCurrentNumber() const;

    int GetQuestionCount() const;

    // Checks the answer, saves it to the history and moves on. An empty answer counts as a mistake
    bool SubmitAnswer(const std::string& user_input);

    const Statistics& GetStatistics() const;

    const std::vector<AnswerRecord>& GetHistory() const;

    std::vector<std::shared_ptr<IQuestion>> GetMistakes() const;

    // Creates a mini-training consisting only of incorrectly answered questions
    TrainingSession CreateMistakesReview() const;

private:
    void Reset();

    std::vector<std::shared_ptr<IQuestion>> questions;
    std::size_t current_index = 0;
    std::vector<AnswerRecord> history;
    Statistics statistics;
};

#endif
