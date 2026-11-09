#include <vector>
#include <string>
#include <algorithm> // For std::stable_sort
#include <stdexcept>
#include "RecommendationSystem.h"

namespace {

std::string JoinWithAnd(const std::vector<std::string>& parts) {
    std::string result;
    for (std::size_t i = 0; i < parts.size(); i++) {
        if (i > 0)
            result += (i + 1 == parts.size()) ? " и " : ", ";
        result += parts[i];
    }
    return result;
}

std::string GetCategoryTitle(int category_id, const DataManager<Category>& categories) {
    try {
        return "«" + categories.GetById(category_id)->GetName() + "»";
    }
    catch (const std::runtime_error&) {
        return "№" + std::to_string(category_id);
    }
}

}

bool Recommendation::IsEmpty() const {
    return weak_category_ids.empty() && weak_difficulties.empty();
}

RecommendationSystem::RecommendationSystem(int threshold_percent) : threshold(threshold_percent) {
}

Recommendation RecommendationSystem::Analyze(const Statistics& stats) const {
    Recommendation result;

    const auto& cat_stats = stats.GetCategoryStats();
    for (const auto& item : cat_stats) {
        if (item.second.total > 0 && item.second.GetPercent() < threshold)
            result.weak_category_ids.push_back(item.first);
    }
    std::stable_sort(result.weak_category_ids.begin(), result.weak_category_ids.end(), [&cat_stats](int a, int b) {
            return cat_stats.at(a).GetPercent() < cat_stats.at(b).GetPercent();
        });

    for (const auto& item : stats.GetDifficultyStats()) {
        if (item.second.total > 0 && item.second.GetPercent() < threshold)
            result.weak_difficulties.push_back(item.first);
    }
    return result;
}

std::string RecommendationSystem::BuildText(const Recommendation& recommendation, const DataManager<Category>& categories) const {
    if (recommendation.IsEmpty()) {
        return "Отличный результат! Во всех темах и на всех уровнях сложности не меньше " + std::to_string(threshold) +
            "% правильных ответов. Попробуйте более дорогие вопросы или новые темы.";
    }

    std::string topics_part;
    std::string bands_part;

    if (!recommendation.weak_category_ids.empty()) {
        std::vector<std::string> names;
        for (int id : recommendation.weak_category_ids)
            names.push_back(GetCategoryTitle(id, categories));
        std::string word = (names.size() == 1) ? "тему " : "темы ";
        topics_part = word + JoinWithAnd(names);
    }

    if (!recommendation.weak_difficulties.empty()) {
        std::vector<std::string> bands;
        for (const auto& difficulty : recommendation.weak_difficulties)
            bands.push_back("«" + difficulty + "»");
        bands_part = (bands.size() == 1 ? "вопросы уровня " : "вопросы уровней ") + JoinWithAnd(bands);
    }

    std::string advice;
    if (topics_part.empty())
        advice = bands_part;
    else
        if (bands_part.empty())
            advice = topics_part;
        else {
            std::string connector = (recommendation.weak_category_ids.size() == 1) ? " и " : ", а также ";
            advice = topics_part + connector + bands_part;
        }

    return "Рекомендуется потренировать " + advice + ".";
}

int RecommendationSystem::GetThreshold() const {
    return threshold;
}
