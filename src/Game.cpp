#include <random>    // For a random number generator
#include <algorithm> // For std::shuffle
#include <vector>
#include <memory>
#include <string>
#include "Game.h"

Game::Game() : the_mode(GameMode::Classic) {

}

void Game::SetMode(GameMode mode) {
    the_mode = mode;
}

void Game::GenerateBoard(const std::vector<std::shared_ptr<Category>>& selected_categories) {
    active_categories = selected_categories;
    std::random_device rd; // Obtaining a random "seed" from the OS
    std::mt19937 g(rd());  // Mersenne Twister algorithm
    std::shuffle(active_categories.begin(), active_categories.end(), g);
}

bool Game::AnswerQuestion(std::shared_ptr<IQuestion> question, const std::string& user_input) {
    bool is_correct = question->CheckAnswer(user_input);
    session.ProcessResult(question->GetCost(), is_correct, question->GetId());

    return is_correct;
}

const GameSession& Game::GetSession() const {
    return session;
}