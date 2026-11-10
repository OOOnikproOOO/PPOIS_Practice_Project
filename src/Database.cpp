#include <stdexcept> // For errors
#include <vector>
#include <string>
#include <sstream>
#include "Database.h"
#include "DatabaseSeeds.h"
#include "StandardQuestion.h"
#include "ImageQuestion.h"
#include "AudioQuestion.h"

std::vector<std::string> SplitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty() && token.back() == '.') {
            token.pop_back();
        }
        tokens.push_back(token);
    }
    return tokens;
}

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

void Database::Initialize() {
    const char* sql = GetDatabaseInitSql();

    char* error_msg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &error_msg) != SQLITE_OK) {
        std::string err(error_msg);
        sqlite3_free(error_msg);
        throw std::runtime_error("Ошибка при инициализации базы данных: " + err);
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
    const char* sql = "SELECT id, category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path FROM questions;";
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
        const unsigned char* alts_ptr = sqlite3_column_text(stmt, 6);
        const unsigned char* type_ptr = sqlite3_column_text(stmt, 7);
        const unsigned char* media_ptr = sqlite3_column_text(stmt, 8);

        std::string text = text_ptr ? reinterpret_cast<const char*>(text_ptr) : "";
        std::string diff = diff_ptr ? reinterpret_cast<const char*>(diff_ptr) : "";
        std::string answer = ans_ptr ? reinterpret_cast<const char*>(ans_ptr) : "";
        std::string alts_raw = alts_ptr ? reinterpret_cast<const char*>(alts_ptr) : "";
        std::string type = type_ptr ? reinterpret_cast<const char*>(type_ptr) : "standard";
        std::string media_path = media_ptr ? reinterpret_cast<const char*>(media_ptr) : "";

        std::vector<std::string> alts = SplitString(alts_raw, '|');

        if (type == "image") {
            auto question = std::make_shared<ImageQuestion>(id, cat_id, cost, text, diff, answer, alts, media_path);
            question_manager.Add(question);
        }
        else 
            if (type == "audio") {
                auto question = std::make_shared<AudioQuestion>(id, cat_id, cost, text, diff, answer, alts, media_path);
                question_manager.Add(question);
            }
            else {
                auto question = std::make_shared<StandardQuestion>(id, cat_id, cost, text, diff, answer, alts);
                question_manager.Add(question);
            }
    }

    sqlite3_finalize(stmt);
}