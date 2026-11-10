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
    Game();

    void SetMode(GameMode mode);

    void GenerateBoard(const std::vector<std::shared_ptr<Category>>& selected_categories);

    // Processing the user response
    bool AnswerQuestion(std::shared_ptr<IQuestion> question, const std::string& user_input);

    const GameSession& GetSession() const;

private:
    GameSession session;
    GameMode the_mode;
    std::vector<std::shared_ptr<Category>> active_categories;
};

#endif