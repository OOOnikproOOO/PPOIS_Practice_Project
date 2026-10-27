#include <stdexcept> // For errors
#include <vector>
#include <string>
#include <sstream>
#include "Database.h"
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
    const char* sql = R"(
        DROP TABLE IF EXISTS questions;
        DROP TABLE IF EXISTS categories;

        CREATE TABLE categories (
            id INTEGER PRIMARY KEY,
            name TEXT UNIQUE
        );

        CREATE TABLE questions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            category_id INTEGER,
            cost INTEGER NOT NULL,
            text TEXT NOT NULL,
            difficulty TEXT,
            correct_answer TEXT NOT NULL,
            alternatives TEXT,
            type TEXT DEFAULT 'standard',
            media_path TEXT DEFAULT '',
            FOREIGN KEY (category_id) REFERENCES categories (id),
            UNIQUE(category_id, cost)
        );

        -- ==========================================
        -- Тема 1: Эдем
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (1, 'Эдем');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (1, 100, 'Согласно ЭТОМУ ПРОИЗВЕДЕНИЮ, земной рай располагается на вершине горы Чистилища.', 'Легко', '«Божественная комедия»', '«Божественная комедия»|"Божественная комедия"|«божественная комедия»|"божественная комедия"|Божественная комедия|божественная комедия|«Божественной комедии»|"Божественной комедии"|«божественной комедии»|"божественной комедии"|Божественной комедии|божественной комедии');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (1, 200, 'В трилогии Гарри Гаррисона «Эдем» ОНИ не вымерли, а эволюционировали в разумных существ.', 'Легко', 'Динозавры', 'Динозавры|динозавры');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (1, 300, 'В начале 2000-х на территории старого карьера в Корнуолле были построены купола, под которыми расположился ОН под названием «Эдем».', 'Средне', 'Ботанический сад', 'Ботанический сад|ботанический сад');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (1, 400, 'В ЭТОМ ГОРОДЕ, давшем название заливу, по легенде, находятся могилы Авеля и Каина.', 'Сложно', 'Аден', 'Аден|Адене|аден|адене');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (1, 500, 'Отвечая на вопрос, а был ли у Адама пупок, креационист Гари Паркер говорит, что даже деревья в саду Эдема были без НИХ.', 'Сложно', 'Годовые кольца', 'Годовые кольца|годовые кольца|Годовых колец|годовых колец|Колец|колец');

        -- ==========================================
        -- Тема 2: Кулинария 
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (2, 'Кулинария');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (2, 100, 'Именно такие два названия носят плоды оливкового дерева.', 'Легко', 'Маслины и оливки', 'Маслины и оливки|маслины и оливки|Маслины, оливки|маслины, оливки|Оливки и маслины|оливки и маслины|Оливки, маслины|оливки, маслины');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (2, 200, 'Именно так называется разогретый жир, в который погружаются продукты для жарки.', 'Легко', 'Фритюр', 'Фритюр|фритюр');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (2, 300, 'Именно так называется употребляемая как пряность высушенная и размельчённая корка цитрусовых.', 'Средне', 'Цедра', 'Цедра|цедра');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (2, 400, 'От этого огородного овоща в пищу идут молодые побеги стеблей, которым не дают прорасти из земли.', 'Сложно', 'Спаржа', 'Спаржа|спаржа');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (2, 500, 'Именно так называются сумчатые подземные грибы, которые растут на глубине 10-20 см.', 'Сложно', 'Трюфели', 'Трюфели|трюфели|Трюфель|трюфель');

        -- ==========================================
        -- Тема 3: И то, и другое
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (3, 'И то, и другое');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (3, 100, 'Это и невысокая печь с дымоходом под полом, и неофициальное название одного из общественных видов транспорта.', 'Легко', 'Подземка', 'Подземка|подземка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (3, 200, 'Это и название аналога современного министерства в Русском государстве с XVI до начала XVII вв.', 'Легко', 'Приказ', 'Приказ|приказ');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (3, 300, 'Это и нарядно украшенные тёплые женские полусапожки, и животные из одноименного семейства.', 'Средне', 'Коты', 'Коты|коты');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (3, 400, 'Это и мужской короткий однобортный сюртук с круглыми фалдами, и сокращенное название «носителя информации».', 'Сложно', 'Визитка', 'Визитка|визитка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (3, 500, 'Это и беспокойство скота от оводов, слепней и других насекомых, и скучное однообразное занятие.', 'Сложно', 'Нуда', 'Нуда|нуда');

        -- ==========================================
        -- Тема 4: Грешная тема
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (4, 'Грешная тема');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (4, 100, 'Именно так в религиозной этике называется моральное зло, состоящее в нарушении воли Бога.', 'Легко', 'Грех', 'Грех|грех');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (4, 200, 'Русские в XVII в. называли его «греховным плодом», а мы называем его «золотым яблоком».', 'Легко', 'Помидор', 'Помидор|помидор|Томат|томат');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (4, 300, 'Миро Антонио утверждал, что единственный, кому можно простить все грехи — это именно ОН.', 'Средне', 'Ты сам', 'Ты сам|ты сам|Ты|ты|Сам|сам');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (4, 400, 'Среди произведений Чингиза Абдуллаева есть ОНА для грешников и для дураков.', 'Сложно', 'Альтернатива', 'Альтернатива|альтернатива');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (4, 500, 'Именно ОН является автором картины «Грехопадение», написанной около 1570 г.', 'Сложно', 'Тициан', 'Тициан|тициан');

        -- ==========================================
        -- Тема 5: Фобии
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (5, 'Фобии');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (5, 100, 'Гиппопотомонстросескиппедалофобия — это страх чего?', 'Легко', 'Длинных и сложных слов', 'Длинных и сложных слов|длинных и сложных слов|Длинных, сложных слов|длинных, сложных слов|Сложных и длинных слов|сложных и длинных слов|Сложных, длинных слов|сложных, длинных слов|Длинных слов|длинных слов|Сложных слов|сложных слов');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (5, 200, 'Именно так называется страх перед страхами.', 'Легко', 'Фобофобия', 'Фобофобия|фобофобия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (5, 300, 'У Гоголя, по отзывам современников, наблюдались признаки тафефобии — боязни именно этого.', 'Средне', 'Быть погребенным заживо', 'Быть погребенным заживо|быть погребенным заживо|Быть погребённым заживо|быть погребённым заживо|Быть погребенным|быть погребенным|Быть погребённым|быть погребённым|Быть заживо погребенным|быть заживо погребенным|Быть заживо погребённым|быть заживо погребённым');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (5, 400, 'Боязнь этого называется никтофобия.', 'Сложно', 'Темноты', 'Темноты|темноты|Темнота|темнота|Темь|темь|Ночи|ночи|Ночь|ночь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (5, 500, 'Так называется страх перед куклами, манекенами, роботами.', 'Сложно', 'Педиофобия', 'Педиофобия|педиофобия');

        -- ==========================================
        -- Тема 6: Кошачья тема
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (6, 'Кошачья тема');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (6, 100, 'Легенда гласит, что полосатые кошки имеют букву "М" на голове, потому что кошек любил гладить ОН.', 'Легко', 'Пророк Мухаммед', 'Пророк Мухаммед|пророк Мухаммед|пророк мухаммед|Пророк мухаммед|Мухаммед|мухаммед');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (6, 200, 'Рекорд, установленный Энди, составил шестнадцать ИХ. Коту очень повезло.', 'Легко', 'Этажей', 'Этажей|этажей|Этажи|этажи|Этаж|этаж');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (6, 300, 'Кошка Литтл Никки обошлась владельцу в 50 тысяч долларов, так как является ТАКОЙ.', 'Средне', 'Клонированной', 'Клонированной|клонированной|Клонированная|клонированная|Клон|клон|Клоном|клоном');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (6, 400, 'Если в Египте кошку хоронили на кладбище животных, то вместе с кошкой в могилу помещались ОНИ.', 'Сложно', 'Мумифицированные мыши', 'Мумифицированные мыши|мумифицированные мыши|Мумии мышей|мумии мышей');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (6, 500, 'По словам директора, интервью и съемки по ИХ поводу случаются не реже, чем про Рембрандта.', 'Сложно', 'Эрмитажные коты', 'Эрмитажные коты|эрмитажные коты|Эрмитажных котов|эрмитажных котов|Котов Эрмитажа|котов Эрмитажа|котов эрмитажа');

        -- ==========================================
        -- Тема 7: Письменность
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (7, 'Письменность');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (7, 100, 'В ЕЁ предшественнице использовалось 12 точек — в два раза больше, чем в ней самой.', 'Легко', 'Азбука Брайля', 'Азбука Брайля|азбука Брайля|Азбука брайля|азбука брайля|Шрифт Брайля|шрифт Брайля|Шрифт брайля|шрифт брайля');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (7, 200, 'Использование латинского алфавита в славянском языке обычно означает доминирование ЕГО в регионе.', 'Легко', 'Католичество', 'Католичество|католичество');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (7, 300, 'Класс объектов в НЁМ задается с помощью цвета нити.', 'Средне', 'Кипу', 'Кипу|кипу|Узелковое письмо|узелковое письмо|Узелковом письме|узелковом письме');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (7, 400, 'Для того чтобы скопировать Бехистунскую надпись, Генри Роулинсону пришлось применить навыки в ЭТОМ неолимпийском ВИДЕ СПОРТА.', 'Сложно', 'Скалолазание', 'Скалолазание|скалолазание|Альпинизм|альпинизм|Скалолазании|скалолазании|Альпинизме|альпинизме');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (7, 500, 'ТАКАЯ ФОРМА ЗАПИСИ называется "ромадзи".', 'Сложно', 'Запись японских слов латиницей', 'Запись японских слов латиницей|запись японских слов латиницей|Запись латиницей японских слов|запись латиницей японских слов|японские слова латиницей|Японские слова латиницей|Латиница японских слов|латиница японских слов');

        -- ==========================================
        -- Тема 8: День, который мы празднуем
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (8, 'День, который мы празднуем');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (8, 100, 'Харви Бэлл придумал отмечать Международный День Улыбки. В основном Бэлл известен авторством ЭТОГО ИЗОБРАЖЕНИЯ.', 'Легко', 'Смайлик', 'Смайлик|смайлик|Смайл|смайл|:)|^-^|^^');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (8, 200, 'Международный день ЭТОГО празднуется 28 декабря. В этот день 1895 года состоялся первый платный сеанс.', 'Легко', 'Кино', 'Кино|кино|Киноматограф|киноматограф|Киноматографа|киноматографа');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (8, 300, '23 августа — Европейский день памяти жертв нацизма и ЕГО.', 'Средне', 'Сталинизм', 'Сталинизм|сталинизм|Сталинизма|сталинизма');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (8, 400, 'Празднования в день ЭТОЙ ВЕЛИЧИНЫ измерения начинают в 6:02 утра и заканчивают в 6:02 вечера.', 'Сложно', 'Моль', 'Моль|моль');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (8, 500, 'В Западном Мэриленде живет ОН по имени Мюррей.', 'Сложно', 'Сурок', 'Сурок|сурок');

        -- ==========================================
        -- Тема 9: Запреты
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (9, 'Запреты');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (9, 100, 'После ЭТОГО СОБЫТИЯ в Китае был запрещен цветок жасмина.', 'Легко', 'Тунисская революция', 'Тунисская революция|тунисская революция|Жасминовая революция|жасминовая революция|революция в Тунисе|Революция в Тунисе|революция в тунисе');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (9, 200, 'ОНА запрещена во многих странах, но если выращивать в бассейне и кормить только морскими звёздами — безвредна.', 'Легко', 'Рыба фугу', 'Рыба фугу|рыба фугу|Рыба Фугу|рыба Фугу|Фугу|фугу');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (9, 300, 'Запрет на продукт ИЗ ЭТОГО РАСТЕНИЯ в России был введен после Московского пожара 1634 года.', 'Средне', 'Табак', 'Табак|табак|Табака|табака');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (9, 400, 'В Саудовской Аравии В ЭТОТ ДЕНЬ запрещено продавать любые товары красного цвета.', 'Сложно', 'День Святого Валентина', 'День Святого Валентина|день Святого Валентина|День Св. Валентина|день Св. Валентина|День св. Валентина|день св. Валентина|День Св.Валентина|день Св.Валентина|День св.Валентина|день св.Валентина');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (9, 500, 'Сейчас в Китае блюдо ИЗ НЕЁ запрещено. Чтобы достать её, придётся давать взятку в ресторане.', 'Сложно', 'Медвежья лапа', 'Медвежья лапа|медвежья лапа|Медвежьей лапы|медвежьей лапы|Лапы медведя|лапы медведя');

        -- ==========================================
        -- Тема 10: Буратино был тупой и не только он
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (10, 'Буратино был тупой и не только он');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (10, 100, '«Для них каждый день безумнее предыдущего», — теглайн ЭТОГО ФИЛЬМА 1994 года.', 'Легко', '«Тупой и еще тупее»', '«Тупой и еще тупее»|"Тупой и еще тупее"|«тупой и еще тупее»|"тупой и еще тупее"|«Тупой и ещё тупее»|"Тупой и ещё тупее"|«тупой и ещё тупее»|"тупой и ещё тупее"|Тупой и еще тупее|тупой и еще тупее|Тупой и ещё тупее|тупой и ещё тупее');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (10, 200, 'Интересно, что ЭТА СОЦИАЛЬНАЯ РЕКЛАМА (Dumb ways to die) была заблокирована в России за пропаганду суицида.', 'Легко', '«Глупые способы умереть»', '«Глупые способы умереть»|"Глупые способы умереть"|«глупые способы умереть»|"глупые способы умереть"|Глупые способы умереть|глупые способы умереть|«Тупые способы умереть»|"Тупые способы умереть"|«тупые способы умереть»|"тупые способы умереть"|Тупые способы умереть|тупые способы умереть');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (10, 300, 'На специальных сайтах, посвящённых ИМ, в первую очередь показан список штатов США.', 'Средне', 'Глупые законы', 'Глупым законам|глупым законам|Тупым законам|тупым законам|Глупые законы|глупые законы|Тупые законы|тупые законы');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (10, 400, 'Эпизод сериала «Глупые симфонии» под названием «Маленькая мудрая курочка» стал дебютом для ЭТОГО ПЕРСОНАЖА.', 'Сложно', 'Дональд Дак', 'Дональд Дак|дональд дак|Дональд дак|дональд Дак|Donald Duck|Donald duck|donald Duck|donald duck');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (10, 500, 'В полном названии эпизода «Южного парка» «Тупое преступление Картмана» присутствует ЭТО ЧИСЛО.', 'Сложно', '2000', '2000|две тысячи|Две тысячи');

        -- ==========================================
        -- Тема 11: Объекты всемирного наследия ЮНЕСКО
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (11, 'Объекты всемирного наследия ЮНЕСКО');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (11, 100, 'ЭТИ ДВА ЗАМКА на территории Беларуси также относятся к объектам всемирного наследия ЮНЕСКО.', 'Легко', 'Мирский и Несвижский замки', 'Мирский и Несвижский замки|Несвижский и Мирский замки|Мирский, Несвижский замки|Несвижский, Мирский замки|Мирский и Несвижский|Несвижский и Мирский|замки в Мире и Несвиже|Замки в Мире и Несвиже|Замки в Несвиже и Мире|замки в Несвиже и Мире|Замки в Несвиже, Мире|замки в Несвиже, Мире|Несвижский замок, Мирский замок|Мирский замок, Несвижский замок|Несвижский замок и Мирский замок|Мирский замок и Несвижский замок');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (11, 200, 'Среди объектов всемирного наследия ЮНЕСКО в Испании отдельным пунктом указан комплекс работ ЭТОГО ЧЕЛОВЕКА в Барселоне.', 'Легко', 'Антонио Гауди', 'Антонио Гауди|антонио гауди|Гауди|гауди|А.Гауди|А. Гауди');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (11, 300, 'К объектам всемирного наследия ЮНЕСКО в Италии относится, в том числе, лагуна ЭТОГО ГОРОДА.', 'Средне', 'Венеция', 'Венеция|венеция|Венеции|венеции');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (11, 400, 'ЭТОТ ОБЪЕКТ получил статус всемирного наследия ЮНЕСКО Польши в 1979 году, а в 1992 году расширился.', 'Сложно', 'Беловежская пуща', 'Беловежская пуща|беловежская пуща');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (11, 500, 'Одним из немногочисленных кандидатов в объекты всемирного наследия ЮНЕСКО В ЭТОЙ СТРАНЕ являются рыцарские укрепления вокруг гаваней.', 'Сложно', 'Мальта', 'Мальта|мальта|Мальте|мальте');

        -- ==========================================
        -- Тема 12: Не только валюты
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (12, 'Не только валюты');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (12, 100, 'Так называемый «аптекарский ОН» равен 12 унциям.', 'Легко', 'Фунт', 'Фунт|фунт');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (12, 200, 'Альфой ЭТОГО СОЗВЕЗДИЯ является звезда Регул, которую также называют «Сердцем».', 'Легко', 'Лев', 'Лев|лев|Льва|льва');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (12, 300, 'В Древней Греции ЭТИМ СЛОВОМ в широком смысле обозначался любой представитель «семейства» щипковых струнных.', 'Средне', 'Лира', 'Лира|лира|Лирой|лирой');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (12, 400, 'Из-за усов, в ЕГО английском названии упомянут кот (Catfish).', 'Сложно', 'Сом', 'Сом|сом|Сома|сома');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (12, 500, 'ЕЁ кельтская разновидность называлась «торквес», изготавливалась из драгоценных металлов и служила наградой.', 'Сложно', 'Гривна', 'Гривна|гривна|Гривны|гривны');

        -- ==========================================
        -- Тема 13: Не только мультфильмы студии «Пиксар»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (13, 'Не только мультфильмы студии «Пиксар»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (13, 100, 'Первые ОНИ в Древней Греции описывались как «ящик для одноколесного транспортного средства».', 'Легко', 'Тачки', 'Тачки|тачки');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (13, 200, 'Серия документальных фильмов об «Apple», «Microsoft», «Facebook» и других называлась «ОНИ».', 'Легко', '«Корпорация монстров»', '«Корпорация монстров»|"Корпорация монстров"|«корпорация монстров»|"корпорация монстров"|Корпорация монстров|корпорация монстров');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (13, 300, 'Фёдор Шаляпин, живя в Париже, называл ЭТО «татарским салатом».', 'Средне', 'Рататуй', 'Рататуй|рататуй');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (13, 400, 'Персонажи романа «Таинственный остров», узнав о человеке, который незримо им помогает, снаряжают экспедицию С ТАКОЙ ЦЕЛЬЮ.', 'Сложно', 'В поисках Немо', 'В поисках Немо|в поисках немо|в поисках Немо');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (13, 500, 'Одной из основных задач ЭТОГО БОЕВОГО ПОРЯДКА является расстройство сомкнутых боевых порядков противника.', 'Сложно', 'Лава', 'Лава|лава|Лавы|лавы');

        -- ==========================================
        -- Тема 14: Полезная тема
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (14, 'Полезная тема');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (14, 100, 'В песне рэпера Дяди Жени постсоветскому правительству достались ОНИ и бесполезное население.', 'Легко', 'Полезные ископаемые', 'Полезные ископаемые|полезные ископаемые|ископаемые');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (14, 200, 'Полезными евреями в Российской империи были купцы первой гильдии... но главное, что все они могли жить ТАМ.', 'Легко', 'За чертой оседлости', 'За чертой оседлости|за чертой оседлости');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (14, 300, 'На могиле специалиста по полезной нагрузке Илана Рамона изображена звезда Давида и стремящийся к ней ОН.', 'Средне', 'Шаттл «Коламбия»', 'Шаттл «Коламбия»|шаттл «Коламбия»|Шаттл «коламбия»|шаттл «коламбия»|Шаттл "Коламбия"|шаттл "Коламбия"|Шаттл "коламбия"|шаттл "коламбия"');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (14, 400, 'В опросе о самом полезном слове ЭТО СЛОВО уступило только слову «подкаст».', 'Сложно', 'Лайфхак', 'Лайфхак|лайфхак|Lifehack|lifehack');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (14, 500, 'В марте 1850 года Никитенко писал, что ЕЁ хотят заменить логикой и психологией.', 'Сложно', 'Философия', 'Философия|философия|Философию|философию');

        -- ==========================================
        -- Тема 15: Дарья, Дарья
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (15, 'Дарья, Дарья');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (15, 100, 'Новосибирский избирком счёл, что Дарья неправильно указала своё отчество, ведь в справке из УФМС было указано именно ТАКОЕ ОТЧЕСТВО.', 'Легко', 'Тимурович', 'Тимурович|тимурович');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (15, 200, 'Плодовитая Дарья Калинина написала уже более полутора сотен произведений В ЭТОМ ЖАНРЕ.', 'Легко', 'Детектив', 'Детектив|детектив|Детектива|детектива');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (15, 300, 'В июле ОНА официально стала жительницей австрийского местечка Обертиллиах.', 'Средне', 'Дарья Домрачева', 'Дарья Домрачева|Д.Домрачева|Д. Домрачева|Домрачева|домрачева|дарья Домрачева|Дарья домрачева');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (15, 400, 'Дмитрий Юрочкин сравнил ИХ с кровеносными сосудами, питавшими сердце, — но теперь без их вклада сердце остановилось.', 'Сложно', 'Сырдарья и Амударья', 'Сырдарья и Амударья|сырдарья и амударья|Амударья и Сырдарья|амурдарья и сырдарья|Сырдарья, Амударья|сырдарья, амударья|Амударья, Сырдарья|амурдарья, сырдарья|Сырдарью и Амударью|сырдарью и амударью|Амударью и Сырдарью|амурдарью и сырдарью|Сырдарью, Амударью|сырдарью, амударью|Амударью, Сырдарью|амурдарью, сырдарью');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (15, 500, 'В ЭТОЙ ОБСЕРВАТОРИИ был открыт астероид, получивший название «Даша».', 'Сложно', 'Крымская астрофизическая обсерватория', 'Крымская астрофизическая обсерватория|крымская астрофизическая обсерватория|Крымской астрофизической обсерватории|крымской астрофизической обсерватории|Крымская обсерватория|крымская обсерватория|Крымской обсерватории|крымской обсерватории|Крымская астрофизическая|крымская астрофизическая|Крымской астрофизической|крымской астрофизической');

        -- ==========================================
        -- Тема 16: Чудеса Света
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (16, 'Чудеса Света');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (16, 100, 'Единственное из семи древних чудес, сохранившееся до наших дней. Назовите эту пирамиду.', 'Легко', 'Пирамида Хеопса', 'Пирамида Хеопса|пирамида Хеопса|пирамида хеопса|Пирамида хеопса|Хеопса|хеопса|Хеопс|хеопс|Великая пирамида Гизы|великая пирамида гизы', 'image', 'assets/images/cheops_pyramid.jpg');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (16, 200, 'Какое легендарное ступенчатое сооружение с садами в Вавилоне изображено на гравюре?', 'Легко', 'Висячие сады Семирамиды', 'Висячие сады Семирамиды|висячие сады Семирамиды|висячие сады семирамиды|Висячие сады|висячие сады|Сады Семирамиды|сады Семирамиды|сады семирамиды', 'image', 'assets/images/hanging_gardens.jpg');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (16, 300, 'Назовите колоссальное навигационное сооружение на острове Фарос возле египетского побережья.', 'Средне', 'Александрийский маяк', 'Александрийский маяк|александрийский маяк|Фаросский маяк|фаросский маяк|Маяк в Александрии|маяк в александрии', 'image', 'assets/images/alexandria_lighthouse.jpg');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (16, 400, 'Перед вами реконструкция гигантской бронзовой статуи бога солнца Гелиоса. Как называлось это чудо?', 'Сложно', 'Колосс Родосский', 'Колосс Родосский|колосс Родосский|колосс родосский|Колосс родосский|Родосский колосс|родосский колосс|Колосс|колосс', 'image', 'assets/images/colossus_rhodes.jpg');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (16, 500, 'Назовите античную монументальную гробницу карийского правителя Мавсола, давшую имя всем подобным сооружениям.', 'Сложно', 'Мавзолей в Галикарнасе', 'Мавзолей в Галикарнасе|мавзолей в Галикарнасе|мавзолей в галикарнасе|Галикарнасский мавзолей|галикарнасский мавзолей|Галикарнас|галикарнас', 'image', 'assets/images/halicarnassus_mausoleum.jpg');

        -- ==========================================
        -- Тема 17: Родом из СССР
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (17, 'Родом из СССР');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (17, 100, 'Прослушайте Игоря Скляра и дайте название его песни.', 'Легко', 'Комарово', 'Комарово|комарово', 'audio', 'assets/audio/komarovo.mp3');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (17, 200, 'Прослушайте хит Аллы Пугачевой и дайте название её песни.', 'Легко', 'Арлекино', 'Арлекино|арлекино|Арлекин|арлекин', 'audio', 'assets/audio/arlekino.mp3');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (17, 300, 'Прослушайте детскую песню композитора Евгения Крылатова на стихи Юрия Энтина и дайте её название.', 'Средне', 'Крылатые качели', 'Крылатые качели|крылатые качели', 'audio', 'assets/audio/krylatye_kacheli.mp3');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (17, 400, 'Прослушайте Ларису Долину и дайте название её песни.', 'Сложно', 'Три белых коня', 'Три белых коня|три белых коня', 'audio', 'assets/audio/tri_belyh_konya.mp3');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives, type, media_path) 
        VALUES (17, 500, 'Прослушайте трек известной советской детской песни Владимира Шаинского и дайте её название.', 'Сложно', 'Голубой вагон', 'Голубой вагон|голубой вагон', 'audio', 'assets/audio/goluboy_vagon.mp3');
    )";

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