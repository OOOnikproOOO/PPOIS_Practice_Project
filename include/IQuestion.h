#ifndef IQUESTION_H
#define IQUESTION_H

#include <string>
#include <vector>
#include <algorithm> // To use STL algorithms

// Base abstract class for all question types
class IQuestion {
public:
    IQuestion(int i, int cat_id, int c, std::string t, std::string diff, std::string p_answer) : 
    id(i), category_id(cat_id), cost(c), text(std::move(t)), difficulty_level(std::move(diff)), primary_answer(std::move(p_answer)) {

    }

    virtual ~IQuestion() = default;

    virtual bool CheckAnswer(const std::string& user_input) const = false;

    int GetCost() const {
        return cost; 
    }

    int GetCategoryId() const { 
        return category_id; 
    }

    std::string GetText() const { 
        return text; 
    }

    std::string GetPrimaryAnswer() const { 
        return primary_answer; 
    }

protected:
    int id;
    int category_id;
    int cost;
    std::string text;
    std::string difficulty_level;
    std::string primary_answer;
};

class StandardQuestion : public IQuestion {
public:
    StandardQuestion(int i, int cat_id, int c, std::string t, std::string diff, std::string p_answer, std::vector<std::string> alts) :
    IQuestion(i, cat_id, c, std::move(t), std::move(diff), std::move(p_answer)), alternative_answers(std::move(alts)) {
    
    }

    bool СheckAnswer(const std::string& user_input) const override {
        if (user_input == primary_answer)
            return true;
        
        auto it = std::find(alternative_answers.begin(), alternative_answers.end(), user_input); // Iterator
        return it != alternative_answers.end();
    }

private:
    std::vector<std::string> alternative_answers;
};

#endif