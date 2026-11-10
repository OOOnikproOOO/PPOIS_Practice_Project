#ifndef STANDARDQUESTION_H
#define STANDARDQUESTION_H

#include <string>
#include <vector>
#include "IQuestion.h"

class StandardQuestion : public IQuestion {
public:
    StandardQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts);
    bool CheckAnswer(const std::string& user_input) const override;

private:
    std::vector<std::string> alternative_answers;
};

#endif