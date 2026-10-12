#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <string>
#include "GameSession.h"
#include "Category.h"
#include "IQuestion.h"

enum class GameMode { Training, Classic };

class Game {
public:
    Game() : the_mode(GameMode::Classic) {
    
    }

    void SetMode(GameMode mode) : the_mode(mode) {

    }

    void GenerateBoard(const std::vector<std::shared_ptr<Category>>& selected_categories) : active_categories(selected_categories) {

    }

    // Processing the user response
    bool AnswerQuestion(std::shared_ptr<IQuestion> question, const std::string& user_input) {
        bool is_correct = question->CheckAnswer(user_input);
        session.ProcessResult(question->GetCost(), is_correct, question->GetId());

        return is_correct;
    }

    const GameSession& GetSession() const {
        return session;
    }

private:
    GameSession session;
    GameMode the_mode;
    std::vector<std::shared_ptr<Category>> active_categories;
};

#endif