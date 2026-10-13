#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <memory> // For std::shared_ptr
#include "IQuestion.h"

class Category {
public:
    Category(int cat_id, std::string& cat_name);

    void AddQuestion(std::shared_ptr<IQuestion> question);

    int GetId() const;

    std::string GetName() const;

    const std::vector<std::shared_ptr<IQuestion>>& GetQuestions() const;

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<IQuestion>> questions;
};

#endif