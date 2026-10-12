#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <memory> // For std::shared_ptr
#include "IQuestion.h"

class Category {
public:
    Category(int cat_id, std::string cat_name) : id(cat_id), name(std::move(cat_name)) {
    
    }

    void AddQuestion(std::shared_ptr<IQuestion> question) {
        questions.push_back(question);
    }

    int GetId() const {
        return id; 
    }

    std::string get_name() const {
        return name;
    }

    const std::vector<std::shared_ptr<IQuestion>>& GetQuestions() const {
        return questions;
    }

private:
    int id;
    std::string name;
    std::vector<std::shared_ptr<IQuestion>> questions;
};

#endif