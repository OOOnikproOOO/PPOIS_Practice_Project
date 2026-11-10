#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <vector>

class GameSession {
public:
    // Logic for point calculation and statistics updates
    void ProcessResult(int points, bool is_correct, int question_id);

    bool IsQuestionPlayed(int question_id) const;

    int GetScore() const;

    int GetCorrectCount() const;

    int GetIncorrectCount() const;

private:
    int the_score = 0;
    int correct_answers = 0;
    int incorrect_answers = 0;
    std::vector<int> played_question_ids;
};

#endif