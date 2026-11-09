#ifndef STATISTICS_H
#define STATISTICS_H

#include <map> // For storing data as key-value pairs
#include <string>

// Counter of correct answers for one group of questions (a category or a difficulty level)
struct StatEntry {
    int correct = 0;
    int total = 0;
    int GetPercent() const;
};

class Statistics {
public:
    // difficulty is the question's own difficulty level ("Легко", "Сложно")
    void AddResult(int category_id, const std::string& difficulty, bool is_correct);

    const std::map<int, StatEntry>& GetCategoryStats() const;

    const std::map<std::string, StatEntry>& GetDifficultyStats() const;

    const StatEntry& GetTotal() const;

    bool IsEmpty() const;

private:
    std::map<int, StatEntry> category_stats;
    std::map<std::string, StatEntry> difficulty_stats;
    StatEntry total_stats;
};

#endif
