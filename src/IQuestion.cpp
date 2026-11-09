#include <string>
#include <vector>
#include "IQuestion.h"

IQuestion::IQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer) :
    id(i), category_id(cat_id), cost(c), text(std::move(t)), difficulty_level(std::move(diff)), primary_answer(std::move(p_answer)) {

}

IQuestion::~IQuestion() = default;

bool IQuestion::CheckAnswer(const std::string& user_input) const {
    return false;
}

int IQuestion::GetId() const {
    return id;
}

int IQuestion::GetCategoryId() const {
    return category_id;
}

int IQuestion::GetCost() const {
    return cost;
}

std::string IQuestion::GetDifficulty() const {
    return difficulty_level;
}

std::string IQuestion::GetText() const {
    return text;
}

std::string IQuestion::GetPrimaryAnswer() const {
    return primary_answer;
}