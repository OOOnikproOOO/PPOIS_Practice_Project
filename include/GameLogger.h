#ifndef GAMELOGGER_H
#define GAMELOGGER_H

#include <string>
#include "Statistics.h"

// Appends the history of games to a text log file, one block per finished game
class GameLogger {
public:
    explicit GameLogger(std::string file_path = "game_history.log");

    // Removes control characters and surrounding spaces; an empty name becomes "Игрок"
    static std::string NormalizeUserName(const std::string& raw_name);

    // Returns false if the file could not be written
    bool LogClassicGame(const std::string& user_name, int score, int correct, int incorrect);

    bool LogTraining(const std::string& user_name, const std::string& mode_title, const Statistics& stats, bool aborted);

    const std::string& GetFilePath() const;

private:
    bool Append(const std::string& text) const;
    static std::string Timestamp();

    std::string file_path;
};

#endif
