#ifndef IMAGEQUESTION_H
#define IMAGEQUESTION_H

#include <vector>
#include <string>
#include "IQuestion.h"

class ImageQuestion : public IQuestion {
public:
    ImageQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts, std::string img_path);

    bool CheckAnswer(const std::string& user_input) const override;
    std::string GetImagePath() const;

private:
    std::vector<std::string> alternative_answers;
    std::string image_path;
};

#endif