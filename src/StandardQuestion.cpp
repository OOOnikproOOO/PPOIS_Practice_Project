#include <string>
#include <vector>
#include <algorithm> // To use STL algorithms
#include "StandardQuestion.h"

StandardQuestion::StandardQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts) :
    IQuestion(i, cat_id, c, t, diff, p_answer), alternative_answers(alts) {

}

bool StandardQuestion::CheckAnswer(const std::string& user_input) const {
    if (user_input == primary_answer)
        return true;

    auto it = std::find(alternative_answers.begin(), alternative_answers.end(), user_input); // Iterator
    return it != alternative_answers.end();
}