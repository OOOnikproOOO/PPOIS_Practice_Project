#include <map>
#include <string>
#include "Statistics.h"

int StatEntry::GetPercent() const {
    if (total == 0)
        return 0;
    return (correct * 100 + total / 2) / total;
}

void Statistics::AddResult(int category_id, const std::string& difficulty, bool is_correct) {
    StatEntry& cat_entry = category_stats[category_id];
    StatEntry& diff_entry = difficulty_stats[difficulty];

    cat_entry.total++;
    diff_entry.total++;
    total_stats.total++;

    if (is_correct) {
        cat_entry.correct++;
        diff_entry.correct++;
        total_stats.correct++;
    }
}

const std::map<int, StatEntry>& Statistics::GetCategoryStats() const {
    return category_stats;
}

const std::map<std::string, StatEntry>& Statistics::GetDifficultyStats() const {
    return difficulty_stats;
}

const StatEntry& Statistics::GetTotal() const {
    return total_stats;
}

bool Statistics::IsEmpty() const {
    return total_stats.total == 0;
}
