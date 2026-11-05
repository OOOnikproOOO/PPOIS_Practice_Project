#include <map>
#include <string>
#include "Statistics.h"

CostBand GetCostBand(int cost) {
    if (cost <= 200)
        return CostBand::Easy;
    if (cost <= 300)
        return CostBand::Medium;
    return CostBand::Hard;
}

std::string GetCostBandLabel(CostBand band) {
    switch (band) {
    case CostBand::Easy:
        return "100–200 баллов";
    case CostBand::Medium:
        return "300 баллов";
    default:
        return "400–500 баллов";
    }
}

int StatEntry::GetPercent() const {
    if (total == 0)
        return 0;
    return (correct * 100 + total / 2) / total;
}

void Statistics::AddResult(int category_id, int cost, bool is_correct) {
    StatEntry& cat_entry = category_stats[category_id];
    StatEntry& band_entry = cost_band_stats[GetCostBand(cost)];

    cat_entry.total++;
    band_entry.total++;
    total_stats.total++;

    if (is_correct) {
        cat_entry.correct++;
        band_entry.correct++;
        total_stats.correct++;
    }
}

const std::map<int, StatEntry>& Statistics::GetCategoryStats() const {
    return category_stats;
}

const std::map<CostBand, StatEntry>& Statistics::GetCostBandStats() const {
    return cost_band_stats;
}

const StatEntry& Statistics::GetTotal() const {
    return total_stats;
}

bool Statistics::IsEmpty() const {
    return total_stats.total == 0;
}
