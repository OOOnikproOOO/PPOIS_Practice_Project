#include <vector>
#include <algorithm>
#include "GameSession.h"

void GameSession::ProcessResult(int points, bool is_correct, int question_id) {
    played_question_ids.push_back(question_id);

    if (is_correct) {
        the_score += points;
        correct_answers++;
    }
    else
        incorrect_answers++;
}

bool GameSession::IsQuestionPlayed(int question_id) const {
    return std::find(played_question_ids.begin(), played_question_ids.end(), question_id) != played_question_ids.end();
}

int GameSession::GetScore() const {
   return the_score;
}

int GameSession::GetCorrectCount() const {
    return correct_answers;
}

int GameSession::GetIncorrectCount() const {
   return incorrect_answers;
}