#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <vector>
#include <string>
#include "Statistics.h"
#include "DataManager.h"
#include "Category.h"

// Weak spots of the user found in the training statistics
struct Recommendation {
    std::vector<int> weak_category_ids;     // Sorted from the weakest topic
    std::vector<CostBand> weak_cost_bands;  // In order of increasing cost

    bool IsEmpty() const;
};

class RecommendationSystem {
public:
    // A group is considered weak if its success rate is strictly below the threshold
    explicit RecommendationSystem(int threshold_percent = 60);

    Recommendation Analyze(const Statistics& stats) const;

    // Human-readable advice, e.g. "Рекомендуется потренировать тему «Кино» и вопросы стоимостью 400–500 баллов."
    std::string BuildText(const Recommendation& recommendation, const DataManager<Category>& categories) const;

    int GetThreshold() const;

private:
    int threshold;
};

#endif
