#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <fstream>

#include "Game.h"
#include "Category.h"
#include "DataManager.h"
#include "GameSession.h"
#include "StandardQuestion.h"
#include "ImageQuestion.h"
#include "AudioQuestion.h"
#include "Database.h"
#include "AssetsWork.h"

namespace fs = std::filesystem;

TEST(CategoryTest, BasicGetters) {
    std::string name = "История";
    Category cat(1, name);
    EXPECT_EQ(cat.GetId(), 1);
    EXPECT_EQ(cat.GetName(), "История");
}

TEST(CategoryTest, DifferentIdsAndNames) {
    std::string empty_name = "";
    Category c1(0, empty_name);
    EXPECT_EQ(c1.GetId(), 0);
    EXPECT_TRUE(c1.GetName().empty());

    std::string long_name = "Очень длинное название категории вопросов для викторины";
    Category c2(9999, long_name);
    EXPECT_EQ(c2.GetId(), 9999);
    EXPECT_EQ(c2.GetName(), "Очень длинное название категории вопросов для викторины");
}

TEST(CategoryTest, AddAndGetQuestions) {
    std::string cat_name = "Животные";
    Category cat(5, cat_name);
    EXPECT_TRUE(cat.GetQuestions().empty());

    std::string q_text = "Хвостатый зверь?";
    std::string diff = "Легко";
    std::string ans = "Кот";
    std::vector<std::string> alts = { "кот", "кошка" };

    auto q1 = std::make_shared<StandardQuestion>(101, 5, 100, q_text, diff, ans, alts);
    auto q2 = std::make_shared<StandardQuestion>(102, 5, 200, q_text, diff, ans, alts);

    cat.AddQuestion(q1);
    cat.AddQuestion(q2);

    ASSERT_EQ(cat.GetQuestions().size(), 2);
    EXPECT_EQ(cat.GetQuestions()[0]->GetId(), 101);
    EXPECT_EQ(cat.GetQuestions()[1]->GetId(), 102);
}

TEST(DataManagerTest, AddAndRetrieveMultiple) {
    DataManager<Category> manager;

    std::string n1 = "Кино";
    std::string n2 = "Музыка";
    std::string n3 = "Наука";

    manager.Add(std::make_shared<Category>(1, n1));
    manager.Add(std::make_shared<Category>(2, n2));
    manager.Add(std::make_shared<Category>(3, n3));

    EXPECT_EQ(manager.GetAll().size(), 3);
    EXPECT_EQ(manager.GetById(1)->GetName(), "Кино");
    EXPECT_EQ(manager.GetById(2)->GetName(), "Музыка");
    EXPECT_EQ(manager.GetById(3)->GetName(), "Наука");
}

TEST(DataManagerTest, NonExistingIdThrowsException) {
    DataManager<Category> manager;
    std::string n = "Тест";
    manager.Add(std::make_shared<Category>(5, n));

    EXPECT_THROW(manager.GetById(999), std::exception);
    EXPECT_THROW(manager.GetById(0), std::exception);
    EXPECT_THROW(manager.GetById(-1), std::exception);
}

TEST(DataManagerTest, ClearCollection) {
    DataManager<Category> manager;
    std::string name = "Спорт";
    manager.Add(std::make_shared<Category>(1, name));
    EXPECT_EQ(manager.GetAll().size(), 1);

    manager.Clear();
    EXPECT_TRUE(manager.GetAll().empty());
}

TEST(StandardQuestionTest, CorrectAndIncorrectAnswers) {
    std::string text = "Столица Беларуси?";
    std::string diff = "Легко";
    std::string primary = "Минск";
    std::vector<std::string> alts = { "Минск", "минск", "г. Минск", "город Минск" };

    StandardQuestion q(10, 1, 100, text, diff, primary, alts);

    EXPECT_EQ(q.GetId(), 10);
    EXPECT_EQ(q.GetCategoryId(), 1);
    EXPECT_EQ(q.GetCost(), 100);
    EXPECT_EQ(q.GetText(), "Столица Беларуси?");
    EXPECT_EQ(q.GetPrimaryAnswer(), "Минск");

    EXPECT_TRUE(q.CheckAnswer("Минск"));
    EXPECT_TRUE(q.CheckAnswer("минск"));
    EXPECT_TRUE(q.CheckAnswer("г. Минск"));
    EXPECT_TRUE(q.CheckAnswer("город Минск"));

    EXPECT_FALSE(q.CheckAnswer("Брест"));
    EXPECT_FALSE(q.CheckAnswer("Гомель"));
    EXPECT_FALSE(q.CheckAnswer(""));
}

TEST(StandardQuestionTest, EmptyAlternativesVector) {
    std::string text = "2 + 2 = ?";
    std::string diff = "Легко";
    std::string primary = "4";
    std::vector<std::string> empty_alts;

    StandardQuestion q(20, 1, 200, text, diff, primary, empty_alts);
    EXPECT_TRUE(q.CheckAnswer("4"));
    EXPECT_FALSE(q.CheckAnswer("5"));
}

TEST(ImageQuestionTest, ImagePathAndAnswerCheck) {
    std::string text = "Назовите эту пирамиду";
    std::string diff = "Средне";
    std::string primary = "Хеопса";
    std::vector<std::string> alts = { "Хеопса", "хеопса", "пирамида Хеопса" };
    std::string img_path = "assets/images/cheops_pyramid.jpg";

    ImageQuestion img_q(30, 2, 300, text, diff, primary, alts, img_path);

    EXPECT_EQ(img_q.GetImagePath(), img_path);
    EXPECT_TRUE(img_q.CheckAnswer("Хеопса"));
    EXPECT_TRUE(img_q.CheckAnswer("пирамида Хеопса"));
    EXPECT_FALSE(img_q.CheckAnswer("Сфинкс"));
}

TEST(ImageQuestionTest, PolymorphismViaBasePointer) {
    std::string text = "Чудо света";
    std::string diff = "Сложно";
    std::string primary = "Маяк";
    std::vector<std::string> alts = { "Маяк", "маяк" };
    std::string img_path = "assets/images/lighthouse.jpg";

    std::shared_ptr<IQuestion> question_ptr =
        std::make_shared<ImageQuestion>(31, 2, 500, text, diff, primary, alts, img_path);

    EXPECT_EQ(question_ptr->GetCost(), 500);
    EXPECT_EQ(question_ptr->GetCategoryId(), 2);
    EXPECT_TRUE(question_ptr->CheckAnswer("маяк"));

    auto casted = std::dynamic_pointer_cast<ImageQuestion>(question_ptr);
    ASSERT_NE(casted, nullptr);
    EXPECT_EQ(casted->GetImagePath(), img_path);
}

TEST(AudioQuestionTest, AudioPathAndAnswerCheck) {
    std::string text = "Назовите песню";
    std::string diff = "Легко";
    std::string primary = "Комарово";
    std::vector<std::string> alts = { "Комарово", "комарово", "На недельку до второго" };
    std::string aud_path = "assets/audio/komarovo.mp3";

    AudioQuestion aud_q(40, 3, 200, text, diff, primary, alts, aud_path);

    EXPECT_EQ(aud_q.GetAudioPath(), aud_path);
    EXPECT_TRUE(aud_q.CheckAnswer("Комарово"));
    EXPECT_TRUE(aud_q.CheckAnswer("На недельку до второго"));
    EXPECT_FALSE(aud_q.CheckAnswer("Катюша"));
}

TEST(AudioQuestionTest, PolymorphismDynamicCast) {
    std::string text = "Слушаем трек";
    std::string diff = "Сложно";
    std::string primary = "Голубой вагон";
    std::vector<std::string> alts = { "Голубой вагон", "голубой вагон" };
    std::string aud_path = "assets/audio/goluboy_vagon.mp3";

    std::shared_ptr<IQuestion> question_ptr =
        std::make_shared<AudioQuestion>(41, 3, 500, text, diff, primary, alts, aud_path);

    auto aud_cast = std::dynamic_pointer_cast<AudioQuestion>(question_ptr);
    ASSERT_NE(aud_cast, nullptr);
    EXPECT_EQ(aud_cast->GetAudioPath(), aud_path);

    auto img_cast = std::dynamic_pointer_cast<ImageQuestion>(question_ptr);
    EXPECT_EQ(img_cast, nullptr);
}

TEST(GameSessionTest, InitialState) {
    GameSession session;
    EXPECT_EQ(session.GetScore(), 0);
    EXPECT_FALSE(session.IsQuestionPlayed(1));
    EXPECT_FALSE(session.IsQuestionPlayed(100));
}

TEST(GameSessionTest, ComplexScoringSequence) {
    GameSession session;

    session.ProcessResult(200, true, 1);
    EXPECT_EQ(session.GetScore(), 200);
    EXPECT_TRUE(session.IsQuestionPlayed(1));

    session.ProcessResult(300, false, 2);
    EXPECT_EQ(session.GetScore(), -100);
    EXPECT_TRUE(session.IsQuestionPlayed(2));

    session.ProcessResult(0, false, 3);
    EXPECT_EQ(session.GetScore(), -100);
    EXPECT_TRUE(session.IsQuestionPlayed(3));

    session.ProcessResult(500, true, 4);
    EXPECT_EQ(session.GetScore(), 400);
    EXPECT_TRUE(session.IsQuestionPlayed(4));
}

TEST(GameSessionTest, CountersAccuracyAndNegativePoints) {
    GameSession session;
    EXPECT_EQ(session.GetCorrectCount(), 0);
    EXPECT_EQ(session.GetIncorrectCount(), 0);

    session.ProcessResult(100, true, 1);
    session.ProcessResult(200, false, 2);
    session.ProcessResult(300, true, 3);
    session.ProcessResult(0, false, 4);
    session.ProcessResult(-50, false, 5);

    EXPECT_EQ(session.GetCorrectCount(), 2);
    EXPECT_EQ(session.GetIncorrectCount(), 1);
}

TEST(DatabaseTest, FullInitializationAndSeeding) {
    std::string test_db = "test_game_full.db";
    if (fs::exists(test_db)) {
        fs::remove(test_db);
    }

    {
        Database db(test_db);
        EXPECT_NO_THROW(db.Initialize());

        DataManager<Category> cat_mgr;
        DataManager<IQuestion> q_mgr;

        EXPECT_NO_THROW(db.LoadCategories(cat_mgr));
        EXPECT_NO_THROW(db.LoadQuestions(q_mgr));

        auto categories = cat_mgr.GetAll();
        auto questions = q_mgr.GetAll();

        EXPECT_GE(categories.size(), 2);
        EXPECT_GE(questions.size(), 10);

        int image_count = 0;
        int audio_count = 0;
        for (const auto& q : questions) {
            if (std::dynamic_pointer_cast<ImageQuestion>(q)) image_count++;
            if (std::dynamic_pointer_cast<AudioQuestion>(q)) audio_count++;
        }

        EXPECT_GE(image_count, 5);
        EXPECT_GE(audio_count, 5);
    }

    if (fs::exists(test_db)) {
        fs::remove(test_db);
    }
}

TEST(DatabaseTest, DoubleInitializationDoesNotCrash) {
    std::string test_db = "test_game_idempotent.db";
    if (fs::exists(test_db)) fs::remove(test_db);

    {
        Database db(test_db);
        EXPECT_NO_THROW(db.Initialize());
        EXPECT_NO_THROW(db.Initialize());
    }

    if (fs::exists(test_db)) fs::remove(test_db);
}

TEST(DatabaseHelperTest, SplitStringTrimmingAndEmpty) {
    std::string sample = "Москва.|Минск|Киев.";
    auto result = SplitString(sample, '|');
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Москва");
    EXPECT_EQ(result[1], "Минск");
    EXPECT_EQ(result[2], "Киев");

    auto empty_res = SplitString("", '|');
    EXPECT_TRUE(empty_res.empty());
}

TEST(DatabaseTest, InvalidDatabasePathThrows) {
    EXPECT_THROW({
        Database bad_db("Z:\\non_existent_drive\\invalid.db");
        bad_db.Initialize();
        }, std::runtime_error);
}

TEST(GameClassTest, FullWorkflow) {
    Game game;
    game.SetMode(GameMode::Training);
    game.SetMode(GameMode::Classic);
    EXPECT_EQ(game.GetSession().GetScore(), 0);

    std::string c_name = "Космос";
    auto cat = std::make_shared<Category>(10, c_name);

    std::string q_text = "Первый космонавт?";
    std::string diff = "Легко";
    std::string ans = "Гагарин";
    std::vector<std::string> alts = { "Гагарин", "гагарин", "Юрий Гагарин" };

    auto q = std::make_shared<StandardQuestion>(201, 10, 500, q_text, diff, ans, alts);
    cat->AddQuestion(q);

    std::vector<std::shared_ptr<Category>> board = { cat };
    EXPECT_NO_THROW(game.GenerateBoard(board));

    bool correct_res = game.AnswerQuestion(q, "Гагарин");
    EXPECT_TRUE(correct_res);
    EXPECT_EQ(game.GetSession().GetScore(), 500);
    EXPECT_TRUE(game.GetSession().IsQuestionPlayed(201));

    auto q_wrong = std::make_shared<StandardQuestion>(202, 10, 200, q_text, diff, ans, alts);
    bool wrong_res = game.AnswerQuestion(q_wrong, "Титов");
    EXPECT_FALSE(wrong_res);
    EXPECT_EQ(game.GetSession().GetScore(), 300);
}

TEST(IQuestionBaseTest, BaseCheckAnswerAndGetters) {
    std::string text = "Базовый вопрос";
    std::string diff = "Средне";
    std::string ans = "Базовый ответ";

    IQuestion base_q(999, 7, 400, text, diff, ans);
    EXPECT_EQ(base_q.GetId(), 999);
    EXPECT_EQ(base_q.GetCategoryId(), 7);
    EXPECT_EQ(base_q.GetCost(), 400);
    EXPECT_EQ(base_q.GetText(), "Базовый вопрос");
    EXPECT_EQ(base_q.GetPrimaryAnswer(), "Базовый ответ");
    EXPECT_FALSE(base_q.CheckAnswer("Любой ответ"));
}

TEST(AssetsWorkTest, PathResolvingVariants) {
    std::string fake = "dummy_folder/no_file.jpg";
    EXPECT_EQ(ResolveMediaPath(fake), fake);

    std::string dummy_file = "test_temp_asset.txt";
    std::ofstream out(dummy_file);
    out << "hello";
    out.close();

    std::string resolved = ResolveMediaPath(dummy_file);
    EXPECT_FALSE(resolved.empty());
    EXPECT_TRUE(fs::exists(resolved));

    fs::remove(dummy_file);
}

TEST(AssetsWorkTest, StopAudioWhenNotPlaying) {
    EXPECT_NO_THROW(StopAudioBackground());
}

TEST(AssetsWorkTest, AudioPlaybackTriggers) {
    EXPECT_NO_THROW(PlayAudioBackground("assets/audio/komarovo.mp3"));
    EXPECT_NO_THROW(StopAudioBackground());

    EXPECT_NO_THROW(PlayAudioBackground("invalid_audio_file_path.mp3"));
}

TEST(AssetsWorkTest, ViewerAndResolverEdgeCases) {
    EXPECT_NO_THROW(OpenImageInViewer("non_existent_folder/absent_image.jpg"));

    std::string non_existent = "random_unreal_path/file.png";
    EXPECT_EQ(ResolveMediaPath(non_existent), non_existent);
}