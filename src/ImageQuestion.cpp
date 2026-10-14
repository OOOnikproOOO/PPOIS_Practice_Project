#include <utility>
#include "ImageQuestion.h"

ImageQuestion::ImageQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts, std::string img_path) : 
    IQuestion(i, cat_id, c, t, diff, p_answer), alternative_answers(alts), image_path(std::move(img_path)) {

}

bool ImageQuestion::CheckAnswer(const std::string& user_input) const {
    if (user_input == primary_answer) 
        return true;
    for (const auto& alt : alternative_answers) {
        if (user_input == alt) 
            return true;
    }
    return false;
}

std::string ImageQuestion::GetImagePath() const {
    return image_path;
}