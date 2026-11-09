#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H

#include <vector>
#include <string>
#include "Statistics.h"
#include "DataManager.h"
#include "Category.h"

// Weak spots of the user found in the training statistics
struct Recommendation {
    std::vector<int> weak_category_ids;
    std::vector<std::string> weak_difficulties;
    bool IsEmpty() const;
};

class RecommendationSystem {
public:
    explicit RecommendationSystem(int threshold_percent = 60);

    Recommendation Analyze(const Statistics& stats) const;

    // Human-readable advice, e.g. "Рекомендуется потренировать тему «Кино» и вопросы уровня «Сложно»."
    std::string BuildText(const Recommendation& recommendation, const DataManager<Category>& categories) const;

    int GetThreshold() const;

private:
    int threshold;
};

#endif
