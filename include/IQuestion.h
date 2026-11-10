#ifndef IQUESTION_H
#define IQUESTION_H

#include <string>

// Base abstract class for all question types
class IQuestion {
public:
    IQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer);
    virtual ~IQuestion();

    virtual bool CheckAnswer(const std::string& user_input) const;

    int GetId() const;
    int GetCategoryId() const;
    int GetCost() const;
    std::string GetText() const;
    std::string GetPrimaryAnswer() const;

protected:
    int id;
    int category_id;
    int cost;
    std::string text;
    std::string difficulty_level;
    std::string primary_answer;
};

#endif