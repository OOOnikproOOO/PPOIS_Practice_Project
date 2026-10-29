#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <string>

// Difficulty groups by question cost: 100-200, 300, 400-500
enum class CostBand { Easy, Medium, Hard };

CostBand GetCostBand(int cost);

std::string GetCostBandLabel(CostBand band);

// Counter of correct answers for one group of questions (a category or a cost band)
struct StatEntry {
    int correct = 0;
    int total = 0;

    // Rounded success rate in percent (0 if there were no questions)
    int GetPercent() const;
};

// Training results grouped by categories and difficulty
class Statistics {
public:
    void AddResult(int category_id, int cost, bool is_correct);

    const std::map<int, StatEntry>& GetCategoryStats() const;

    const std::map<CostBand, StatEntry>& GetCostBandStats() const;

    const StatEntry& GetTotal() const;

    bool IsEmpty() const;

private:
    std::map<int, StatEntry> category_stats;
    std::map<CostBand, StatEntry> cost_band_stats;
    StatEntry total_stats;
};

#endif
