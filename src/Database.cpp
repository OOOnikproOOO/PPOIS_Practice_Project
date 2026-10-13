#include <stdexcept> // For errors
#include <vector>
#include <string>
#include "Database.h"
#include "StandardQuestion.h"

Database::Database(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
        std::string error_msg = sqlite3_errmsg(db);
        throw std::runtime_error("Ошибка при открытии базы данных: " + error_msg);
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

void Database::LoadCategories(DataManager<Category>& category_manager) {
    const char* sql = "SELECT id, name FROM categories;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки SQL-запроса для категорий.");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* name_text = sqlite3_column_text(stmt, 1);
        std::string name = name_text ? reinterpret_cast<const char*>(name_text) : "";

        auto category = std::make_shared<Category>(id, name);
        category_manager.Add(category);
    }

    sqlite3_finalize(stmt);
}

void Database::LoadQuestions(DataManager<IQuestion>& question_manager) {
    const char* sql = "SELECT id, category_id, cost, text, difficulty, correct_answer FROM questions;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Ошибка подготовки SQL-запроса для вопросов.");
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int cat_id = sqlite3_column_int(stmt, 1);
        int cost = sqlite3_column_int(stmt, 2);

        const unsigned char* text_ptr = sqlite3_column_text(stmt, 3);
        const unsigned char* diff_ptr = sqlite3_column_text(stmt, 4);
        const unsigned char* ans_ptr = sqlite3_column_text(stmt, 5);

        std::string text = text_ptr ? reinterpret_cast<const char*>(text_ptr) : "";
        std::string diff = diff_ptr ? reinterpret_cast<const char*>(diff_ptr) : "";
        std::string answer = ans_ptr ? reinterpret_cast<const char*>(ans_ptr) : "";
        std::vector<std::string> alts = {};

        auto question = std::make_shared<StandardQuestion>(id, cat_id, cost, text, diff, answer, alts);
        question_manager.Add(question);
    }

    sqlite3_finalize(stmt);
}