#include <fstream>
#include <utility>
#include <ctime>
#include <string>
#include "GameLogger.h"

GameLogger::GameLogger(std::string path) : file_path(std::move(path)) {
}

std::string GameLogger::NormalizeUserName(const std::string& raw_name) {
    std::string cleaned;
    for (unsigned char ch : raw_name) {
        if (ch >= 32 && ch != 127) // Drop control characters (line breaks, tabs)
            cleaned += static_cast<char>(ch);
    }

    std::size_t begin = cleaned.find_first_not_of(' ');
    if (begin == std::string::npos)
        return "Игрок";
    std::size_t end = cleaned.find_last_not_of(' ');
    return cleaned.substr(begin, end - begin + 1);
}

std::string GameLogger::Timestamp() {
    std::time_t now = std::time(nullptr);
    std::tm local_time{};
#if defined(_WIN32)
    localtime_s(&local_time, &now);
#else
    localtime_r(&now, &local_time);
#endif
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return buffer;
}

bool GameLogger::Append(const std::string& text) const {
    std::ofstream file(file_path, std::ios::app);
    if (!file)
        return false;
    file << text;
    return static_cast<bool>(file);
}

bool GameLogger::LogClassicGame(const std::string& user_name, int score, int correct, int incorrect) {
    std::string text = "[" + Timestamp() + "] Игрок: " + user_name + " | Режим: Классическая игра\n";
    text += "  Итоговый счет: " + std::to_string(score) + "\n";
    text += "  Правильных ответов: " + std::to_string(correct) + ", неверных: " + std::to_string(incorrect) + "\n\n";
    return Append(text);
}

bool GameLogger::LogTraining(const std::string& user_name, const std::string& mode_title, const Statistics& stats, bool aborted) {
    const StatEntry& total = stats.GetTotal();
    std::string text = "[" + Timestamp() + "] Игрок: " + user_name + " | Режим: " + mode_title
        + (aborted ? " (завершена досрочно)" : "") + "\n";
    text += "  Правильных ответов: " + std::to_string(total.correct) + " из " + std::to_string(total.total)
        + " (" + std::to_string(total.GetPercent()) + "%)\n";

    for (const auto& item : stats.GetDifficultyStats()) {
        text += "  Сложность «" + item.first + "»: " + std::to_string(item.second.correct) + " из "
            + std::to_string(item.second.total) + "\n";
    }
    text += "\n";
    return Append(text);
}

const std::string& GameLogger::GetFilePath() const {
    return file_path;
}
