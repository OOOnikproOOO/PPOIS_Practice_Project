#include <string>
#include <vector>
#include <memory>
#include "Category.h"

Category::Category(int cat_id, std::string& cat_name) : id(cat_id), name(std::move(cat_name)) {

}

void Category::AddQuestion(std::shared_ptr<IQuestion> question) {
    questions.push_back(question);
}

int Category::GetId() const {
    return id;
}

std::string Category::GetName() const {
    return name;
}

const std::vector<std::shared_ptr<IQuestion>>& Category::GetQuestions() const {
    return questions;
}