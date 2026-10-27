#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <sqlite3.h> // Standard SQLite library for C++
#include "DataManager.h"
#include "Category.h"
#include "IQuestion.h"

std::vector<std::string> SplitString(const std::string& str, char delimiter);

class Database {
public:
    Database(const std::string& db_path);
    ~Database();

    void Initialize();
    void LoadCategories(DataManager<Category>& category_manager);
    void LoadQuestions(DataManager<IQuestion>& question_manager);

private:
    sqlite3* db;
};

#endif