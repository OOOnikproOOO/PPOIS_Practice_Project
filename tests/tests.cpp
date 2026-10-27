#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

#include "Category.h"
#include "DataManager.h"
#include "GameSession.h"
#include "StandardQuestion.h"
#include "ImageQuestion.h"
#include "AudioQuestion.h"

TEST(CategoryTest, CreationAndGetters) {
    std::string cat_name = "История";
    Category cat(1, cat_name);

    EXPECT_EQ(cat.GetId(), 1);
    EXPECT_EQ(cat.GetName(), "История");
}

TEST(DataManagerTest, AddAndRetrieve) {
    DataManager<Category> manager;

    std::string name1 = "Кино";
    std::string name2 = "Музыка";
    auto cat1 = std::make_shared<Category>(1, name1);
    auto cat2 = std::make_shared<Category>(2, name2);

    manager.Add(cat1);
    manager.Add(cat2);

    EXPECT_EQ(manager.GetAll().size(), 2);
    EXPECT_EQ(manager.GetById(1)->GetName(), "Кино");
    EXPECT_EQ(manager.GetById(2)->GetName(), "Музыка");

    EXPECT_THROW(manager.GetById(999), std::exception);
}

TEST(QuestionTest, StandardQuestionLogic) {
    std::string text = "Столица Беларуси?";
    std::string diff = "Легко";
    std::string answer = "Минск";
    std::vector<std::string> alts = { "Минск", "минск", "г. Минск", "город Минск" };

    StandardQuestion q(10, 1, 200, text, diff, answer, alts);

    EXPECT_EQ(q.GetId(), 10);
    EXPECT_EQ(q.GetCategoryId(), 1);
    EXPECT_EQ(q.GetCost(), 200);
    EXPECT_EQ(q.GetText(), "Столица Беларуси?");
    EXPECT_EQ(q.GetPrimaryAnswer(), "Минск");

    EXPECT_TRUE(q.CheckAnswer("Минск"));
    EXPECT_TRUE(q.CheckAnswer("минск"));
    EXPECT_TRUE(q.CheckAnswer("город Минск"));
    EXPECT_TRUE(q.CheckAnswer("г. Минск"));

    EXPECT_FALSE(q.CheckAnswer("Гродно"));
    EXPECT_FALSE(q.CheckAnswer(""));
}

TEST(QuestionTest, ImageQuestionSpecialization) {
    std::string text = "Что на фото?";
    std::string diff = "Средне";
    std::string answer = "Пирамида";
    std::vector<std::string> alts = { "Пирамида", "пирамида" };
    std::string img_path = "assets/images/pyramid.jpg";

    ImageQuestion img_q(11, 2, 300, text, diff, answer, alts, img_path);

    EXPECT_EQ(img_q.GetImagePath(), "assets/images/pyramid.jpg");
    EXPECT_TRUE(img_q.CheckAnswer("Пирамида"));
    EXPECT_TRUE(img_q.CheckAnswer("пирамида"));
    EXPECT_FALSE(img_q.CheckAnswer("Колизей"));

    std::shared_ptr<IQuestion> base_ptr = std::make_shared<ImageQuestion>(img_q);
    EXPECT_EQ(base_ptr->GetCost(), 300);
}

TEST(QuestionTest, AudioQuestionSpecialization) {
    std::string text = "Кто поет?";
    std::string diff = "Сложно";
    std::string answer = "Комарово";
    std::vector<std::string> alts = { "Комарово", "комарово" };
    std::string aud_path = "assets/audio/track.mp3";

    AudioQuestion aud_q(12, 3, 500, text, diff, answer, alts, aud_path);

    EXPECT_EQ(aud_q.GetAudioPath(), "assets/audio/track.mp3");
    EXPECT_TRUE(aud_q.CheckAnswer("Комарово"));
    EXPECT_TRUE(aud_q.CheckAnswer("комарово"));
    EXPECT_FALSE(aud_q.CheckAnswer("Трава у дома"));
}

TEST(GameSessionTest, ScoreAndPlayedStateManagement) {
    GameSession session;

    EXPECT_EQ(session.GetScore(), 0);
    EXPECT_FALSE(session.IsQuestionPlayed(1));

    session.ProcessResult(200, true, 1);
    EXPECT_EQ(session.GetScore(), 200);
    EXPECT_TRUE(session.IsQuestionPlayed(1));

    session.ProcessResult(100, false, 2);
    EXPECT_EQ(session.GetScore(), 100);
    EXPECT_TRUE(session.IsQuestionPlayed(2));

    session.ProcessResult(0, false, 3);
    EXPECT_EQ(session.GetScore(), 100);
    EXPECT_TRUE(session.IsQuestionPlayed(3));
}