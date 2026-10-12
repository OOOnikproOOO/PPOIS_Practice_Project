#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <vector>
#include <algorithm>

class GameSession {
public:
    // Logic for point calculation and statistics updates
    void ProcessResult(int points, bool is_correct, int question_id) {
        played_question_ids.push_back(question_id);

        if (is_correct) {
            the_score += points;
            correct_answers++;
        }
        else
            incorrect_answers++;
    }

    bool IsQuestionPlayed(int question_id) const {
        return std::find(played_question_ids.begin(), played_question_ids.end(), question_id) != played_question_ids.end();
    }

    int GetScore() const { 
        return current_score;
    }

    int GetCorrectCount() const {
        return correct_answers;
    }

    int GetIncorrectCount() const { 
        return incorrect_answers; 
    }

private:
    int the_score = 0;
    int correct_answers = 0;
    int incorrect_answers = 0;
    std::vector<int> played_question_ids;
};

#endif