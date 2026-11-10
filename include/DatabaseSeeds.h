#pragma once

inline const char* GetDatabaseInitSql() {
    return R"(
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

        -- ==========================================
        -- Тема 18: Вокруг спорта
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (18, 'Вокруг спорта');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (18, 100, 'На постере социальной рекламы рядом изображен баскетболист с мячом в руке и человек с сигаретой. Подпись призывает обоих героев ДЕЛАТЬ ЭТО.', 'Легко', 'Бросать', 'Бросать|бросать|Бросить|бросить');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (18, 200, 'Мировая серия "Воздушная гонка", соревнование по аэробатике, проходит под эгидой ЭТОЙ австрийской КОМПАНИИ.', 'Легко', '«Red Bull»', '«Red Bull»|"Red Bull"|«Red Bull GmbH»|"Red Bull GmbH"|Red Bull|red bull|Red Bull GmbH|Ред Булл|ред булл|Ред булл|Редбулл|редбулл');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (18, 300, 'Игровой номер карлика-бейсболиста из одного юмористического сериала состоит из единицы, ЭТОГО и восьмерки.', 'Средне', 'Слэш', 'Слэш|слэш|/|Знак деления|знак деления|Знак «поделить»|знак «поделить»|Знак "поделить"|знак "поделить"|Поделить|поделить|Дробь|дробь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (18, 400, 'По ЕГО словам, бОльшим оскорблением было то, что Рузвельт не удосужился прислать поздравительную телеграмму.', 'Сложно', 'Джесси Оуэнс', 'Джесси Оуэнс|джесси оуэнс|Джесси оуэнс|Оуэнс|оуэнс|Дж. Оуэнс|Дж.Оуэнс');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (18, 500, 'В одном из проектов для церемонии открытия Лондонской Олимпиады планировали создать искусственные облака из НЕЕ. Но задумка оказалась неоправданно дорогой.', 'Сложно', 'Овечья шерсть', 'Овечья шерсть|овечья шерсть|Овечьей шерсти|овечьей шерсти|Шерсть|шерсть|Шерсти|шерсти|Шерсть овцы|шерсть овцы');

        -- ==========================================
        -- Тема 19: Из согласных только «С»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (19, 'Из согласных только «С»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (19, 100, 'Герои книги Юлиуса Фучика и Богумилы Силовой — Слава, Ольга и Сашенька, странствуют по миру в поисках находящихся в бедственном положении людей. А символизируют герои именно ЭТО.', 'Легко', 'SOS', 'SOS|sos|СОС|сос|[Сигнал] SOS|Сигнал SOS|сигнал SOS|сигнал сос|Сигнал сос|Сигнал бедствия|сигнал бедствия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (19, 200, 'ЭТО слово в переводе с латыни означает «заседание». Сдавайте ваши ответы!', 'Легко', 'Сессия', 'Сессия|сессия|Сессии|сессии');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (19, 300, 'На получение национального домена верхнего уровня .ss была подана заявка ЭТОЙ страной. И хотя регистрация прошла успешно, домен всё еще не функционирует.', 'Средне', 'Южный Судан', 'Южный Судан|южный судан|Южного Судана|южного судана');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (19, 400, 'Своим названием ОНА обязана крылатому коню. А одно из ЕЕ дочерних подразделений именуется «Pegatron».', 'Сложно', '«Asus»', '«Asus»|"Asus"|«asus»|"asus"|«ASUS»|"ASUS"|Asus|asus|ASUS|Асус|асус');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (19, 500, 'В ЕГО менее известном произведении «толстый кот, лениво хвостом шевеля, дразнит бабочек».', 'Сложно', 'Исса', 'Исса|исса|Кобаяси Исса|кобаяси исса|Кобаяси исса');

        -- ==========================================
        -- Тема 20: Млекопитающие
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (20, 'Млекопитающие');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (20, 100, 'На рекламном плакате «Фольксваген» представлена система определения усталости. На плакате ОНИ не могут перепрыгнуть высокое заграждение.', 'Легко', 'Овцы', 'Овцы|овцы|Овечки|овечки|Бараны|бараны|Баран|баран|Овца|овца');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (20, 200, 'Мафиозный бухгалтер из одного сериала призывает ганстеров к экономии: ведь остальную ЕЕ часть тоже можно использовать.', 'Легко', 'Лошадь', 'Лошадь|лошадь|Лошади|лошади|Конь|конь|Коня|коня|Голова лошади|голова лошади');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (20, 300, 'На сегодняшний день в Базе Вопросов можно найти уже 57 вопросов, обыгрывающих ЭТО ПРОИЗВЕДЕНИЕ. Ну сколько можно повторять одно и то же?', 'Средне', '«День сурка»', '«День сурка»|"День сурка"|«день сурка»|"день сурка"|День сурка|день сурка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (20, 400, 'В сериале «Bugs» в ЕГО роли была закрытая в заминированном сейфе улика.', 'Сложно', 'Кот Шрёдингера', 'Кот Шрёдингера|кот шрёдингера|Кот Шредингера|кот шредингера|Кота Шрёдингера|кота шрёдингера|Кота Шредингера|кота шредингера');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (20, 500, 'В португальской пословице ОН умер оттого, что долго думал.', 'Сложно', 'Осёл', 'Осёл|осёл|Осел|осел|Ишак|ишак');

        -- ==========================================
        -- Тема 21: Городская
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (21, 'Городская');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (21, 100, 'К НИМ относятся, например, крокодилы в канализации, розуэльский инцидент, летающие стержни и мост плачущих детей.', 'Легко', 'Городские легенды', 'Городские легенды|городские легенды|Городская легенда|городская легенда|Легенды|легенды');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (21, 200, 'Опираясь на известную поговорку, Рим можно назвать ЭТИМ ПАЛИНДРОМОМ из двух слов.', 'Легко', 'Город дорог', 'Город дорог|город дорог');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (21, 300, 'В древние времена люди боролись с ЭТИМ при помощи громкого звука: ради спасения обреченного на уничтожение урожая звонили в колокола или стреляли из пушек.', 'Средне', 'Град', 'Град|град|Градом|градом');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (21, 400, 'В прошлом году освещение ЭТОГО некоторое время зависело от общего настроения пользователей Твиттера: высчитывалось соотношение позитивных и негативных эмоций в сообщениях и оформлялось в виде круговой диаграммы. Такое себе «зеркало души».', 'Сложно', '«Лондонский глаз»', '«Лондонский глаз»|"Лондонский глаз"|«лондонский глаз»|"лондонский глаз"|Лондонский глаз|лондонский глаз|«Глаз Лондона»|"Глаз Лондона"|Глаз Лондона|глаз лондона|London Eye|«London Eye»|"London Eye"|Колесо обозрения в Лондоне|колесо обозрения в Лондоне|колесо обозрения в лондоне');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (21, 500, 'Говоря о непогоде в Палермо, развязавшей руки местным криминальным элементам, автор вопроса добавил к ЭТИМ ДВУМ СЛОВАМ слово «снегом».', 'Сложно', 'Город засыпает', 'Город засыпает|город засыпает');

        -- ==========================================
        -- Тема 22: Транспорт
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (22, 'Транспорт');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (22, 100, 'Первым ЕГО личным транспортным средством стал «Нимбус-2000».', 'Легко', 'Гарри Поттер', 'Гарри Поттер|гарри поттер|Гарри поттер|Поттер|поттер|Гарри|гарри');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (22, 200, 'Мощность ЭТОГО железнодорожного ТРАНСПОРТА составляла всего несколько лошадиных сил.', 'Легко', 'Конка', 'Конка|конка|Конки|конки|Конно-железная городская дорога|конно-железная городская дорога|Конно-железная дорога|конно-железная дорога|Конная железная дорога|конная железная дорога');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (22, 300, '«ОНО» — название серии фотографий Алессандро Космелли о радикальных националистах. В 66% стран мира — ОНО.', 'Средне', 'Правостороннее движение', 'Правостороннее движение|правостороннее движение|Правостороннее|правостороннее');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (22, 400, 'Обладатель сапогов-скороходов мог за один шаг преодолевать ТАКОЕ вполне конкретное РАССТОЯНИЕ.', 'Сложно', 'Семь миль', 'Семь миль|семь миль|7 миль');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (22, 500, '7 сентября 1914 года путь из Парижа к берегам ЭТОЙ РЕКИ проделали около 600 автомобилей такси. И не зря.', 'Сложно', 'Марна', 'Марна|марна|Марны|марны|Река Марна|река марна');

        -- ==========================================
        -- Тема 23: Слова, слова, слова
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (23, 'Слова, слова, слова');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (23, 100, 'Изначально ЭТИМ СЛОВОМ называли преступников, казненных усечением головы.', 'Легко', 'Уголовник', 'Уголовник|уголовник|Уголовники|уголовники');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (23, 200, 'По одной из версий, её имя происходит от древнегреческих слов «пан» (всё) и «дорон» (дар). Какую «банку с червями» открыла она?', 'Легко', 'Ящик', 'Ящик|ящик|Ящик Пандоры|ящик Пандоры|ящик пандоры|Ящик пандоры');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (23, 300, 'Присосавшись к человеку или животному, ОН так обалдевает от вкуса крови, что уже ничего не видит.', 'Средне', 'Слепень', 'Слепень|слепень|Овод|овод');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (23, 400, 'Изначально ОН был чуть раньше, когда Солнце находилось на юге.', 'Сложно', 'Ужин', 'Ужин|ужин');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (23, 500, 'ЭТИМ СЛОВОМ раньше называли слугу, которого в поездке можно было продать или выменять на что-то.', 'Сложно', 'Товарищ', 'Товарищ|товарищ');

        -- ==========================================
        -- Тема 24: Языки мира
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (24, 'Языки мира');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (24, 100, 'Именно этот язык италийской группы в средние века существовал в качестве общего письменного языка западноевропейского общества, католической церкви, науки и частично литературы.', 'Легко', 'Латинский язык', 'Латинский язык|латинский язык|Латынь|латынь|Латинский|латинский');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (24, 200, 'На этих языках говорят некоторые жители Либерии, Республики Кот-д''Ивуар, Ганы, Того, Бенина и Нигерии, а вовсе не лягушки.', 'Легко', 'Языки Ква', 'Языки Ква|языки Ква|языки ква|Ква|ква|Язык ква|язык ква');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (24, 300, 'Именно этот язык германской группы возник в процессе интеграции и смешения нидерландских диалектов с немецким и английским языками, а также с некоторыми местными языками.', 'Средне', 'Африкаанс', 'Африкаанс|африкаанс|Бурский язык|бурский язык|Бурский|бурский');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (24, 400, 'Именно этот семитский язык является официальным в Эфиопии.', 'Сложно', 'Амхарский', 'Амхарский|амхарский|Амхарский язык|амхарский язык');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (24, 500, 'К романским языкам относятся испанский, португальский, каталанский, галисийский; французский, окситанский; итальянский, сардинский; ретороманские; румынский, молдавский, а также именно этот, исчезнувший в XIX века.', 'Сложно', 'Далматинский язык', 'Далматинский язык|далматинский язык|Далматинский|далматинский|Далматский язык|далматский язык|Далматский|далматский');

        -- ==========================================
        -- Тема 25: Поговорим о енотах
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (25, 'Поговорим о енотах');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (25, 100, 'Именно так называют еще обыкновенного енота.', 'Легко', 'Енот-полоскун', 'Енот-полоскун|енот-полоскун|Полоскун|полоскун');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (25, 200, 'Именно так называется соответствующий теме русскоязычный журнал «для мужчин».', 'Легко', '«Енот-потаскун»', '«Енот-потаскун»|"Енот-потаскун"|«енот-потаскун»|"енот-потаскун"|Енот-потаскун|енот-потаскун');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (25, 300, 'Именно так еще называют уссурийского енота, относимого к семейству волчьих.', 'Средне', 'Енотовидная собака', 'Енотовидная собака|енотовидная собака|Енотовидную собаку|енотовидную собаку|Уссурийский енот|уссурийский енот');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (25, 400, 'В названии именно этого центральноамериканского енота присутствует зодиакальное созвездие.', 'Сложно', 'Енот-ракоед', 'Енот-ракоед|енот-ракоед|Ракоед|ракоед');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (25, 500, 'Именно эти енотовые являются исконными обитателями Азии.', 'Сложно', 'Панды', 'Панды|панды|Панда|панда|Малая и большая панды|малая и большая панды|Малая панда|малая панда|Большая панда|большая панда');

        -- ==========================================
        -- Тема 26: Не только то, но и другое
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (26, 'Не только то, но и другое');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (26, 100, 'Это и беспорядок, хаос, и название дома для умалишенных в Лондоне.', 'Легко', 'Бедлам', 'Бедлам|бедлам');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (26, 200, 'Это и кристаллическая слоистая горная порода, и вид ядовитой змеи.', 'Легко', 'Аспид', 'Аспид|аспид|Аспидный сланец|аспидный сланец');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (26, 300, 'Это и простой народ, низы общества, и вид гравировки на металле.', 'Средне', 'Чернь', 'Чернь|чернь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (26, 400, 'Так называли и жребий, и документ, удостоверяющий личность и заменяющий паспорт.', 'Сложно', 'Билет', 'Билет|билет');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (26, 500, 'Это и остроконечный верх здания, шпиль, и порода собак.', 'Сложно', 'Шпиц', 'Шпиц|шпиц');

        -- ==========================================
        -- Тема 27: Третьи
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (27, 'Третьи');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (27, 100, 'Этот материк – третий по величине.', 'Легко', 'Северная Америка', 'Северная Америка|северная америка|Сев. Америка|сев. америка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (27, 200, 'Карибский кризис, по мнению очевидцев, чуть было не спровоцировал это.', 'Легко', 'Третья мировая война', 'Третья мировая война|третья мировая война|Третью мировую войну|третью мировую войну|Третья мировая|третья мировая|Третью мировую|третью мировую');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (27, 300, 'Это название фашистскими нацистами было заимствовано из средневековых мистических учений о третьем царстве.', 'Средне', 'Третий рейх', 'Третий рейх|третий рейх|Третий Рейх|третий Рейх');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (27, 400, 'Он поведал нам историю о Тайне третьей планеты.', 'Сложно', 'Кир Булычёв', 'Кир Булычёв|кир булычёв|Кир Булычев|кир булычев|Булычёв|булычёв|Булычев|булычев');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (27, 500, 'Первым чемпионом мира был англичанин, вторым – немец, третьим – кубинец. А в каком виде спорта?', 'Сложно', 'Шахматы', 'Шахматы|шахматы|В шахматах|в шахматах|В шахматы|в шахматы');

        -- ==========================================
        -- Тема 28: Рак
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (28, 'Рак');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (28, 100, 'Это должен сделать рак, чтобы произошло чудо.', 'Легко', 'Свистнуть на горе', 'Свистнуть на горе|свистнуть на горе|Свистнуть|свистнуть|Свистеть|свистеть');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (28, 200, 'Эти раки своё брюшко часто прячут в пустую раковину брюхоногого моллюска или прячутся в неё целиком.', 'Легко', 'Раки-отшельники', 'Раки-отшельники|раки-отшельники|Рак-отшельник|рак-отшельник|Отшельники|отшельники|Отшельник|отшельник');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (28, 300, 'Канцерогенные вещества – это вещества, которые…', 'Средне', 'Вызывают рак', 'Вызывают рак|вызывают рак|Вызывающие рак|вызывающие рак|Провоцируют рак|провоцируют рак');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (28, 400, 'Между этими знаками Зодиака находится знак Рака.', 'Сложно', 'Между Близнецами и Львом', 'Между Близнецами и Львом|между Близнецами и Львом|между близнецами и львом|Близнецы и Лев|близнецы и лев|Близнецами и Львом|близнецами и львом|Близнецы, Лев|близнецы, лев');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (28, 500, 'Таких неопытных людей с низкими навыками называют раками.', 'Сложно', 'Нубы', 'Нубы|нубы|Нуб|нуб|Noob|noob|Нубики|нубики');

        -- ==========================================
        -- Тема 29: Поэты о птицах
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (29, 'Поэты о птицах');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (29, 100, 'СветлОв назвал ЕГО «оратором деревень».', 'Легко', 'Петух', 'Петух|петух');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (29, 200, 'ЛуговскОй писал, что ОНИ — «Черные гадалки, // Длинные хвосты, // Трефовые кресты».', 'Легко', 'Галки', 'Галки|галки');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (29, 300, '«Это щёголь в птичьем свете, // в красном бархатном берете, // в тонком черном пиджаке, // с червяком в одной руке», — писал о НЕМ Борис КорнИлов.', 'Средне', 'Дятел', 'Дятел|дятел');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (29, 400, '«Пинь-пинь-пинь», — тарарахнул ИМЕННО ОН у ХлЕбникова.', 'Сложно', 'Зинзивер (большая синица)', 'Зинзивер|зинзивер|Большая синица|большая синица|Синица|синица');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (29, 500, 'ВознесЕнский сравнил ИХ с треугольными пловчихами.', 'Сложно', 'Ласточки', 'Ласточки|ласточки|Ласточка|ласточка');

        -- ==========================================
        -- Тема 30: Эвфемизмы
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (30, 'Эвфемизмы');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (30, 100, 'Согласно постановлению Главного государственного санитарного врача ЕГО теперь принято называть «помещение, оборудованное унитазом».', 'Легко', 'Туалет', 'Туалет|туалет|Уборная|уборная|Санузел|санузел');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (30, 200, 'Благодаря Евгению ДОдолеву ЭТО СЛОВОСОЧЕТАНИЕ означает не только мешочниц, медведиц или стеклянниц, но и людей.', 'Легко', 'Ночные бабочки', 'Ночные бабочки|ночные бабочки|Ночная бабочка|ночная бабочка|Бабочки ночные|бабочки ночные');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (30, 300, 'ЭТОТ ЭВФЕМИЗМ для обозначения галлюцинаций впервые зафиксирован в автобиографической повести Джека Лондона «Джон Ячменное Зерно».', 'Средне', 'Розовый слон', 'Розовый слон|розовый слон|Розовые слоны|розовые слоны');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (30, 400, 'Согласно одной из версий, ЭТОТ ЭВФЕМИЗМ восходит к БаЮну, любимцу Бабы Яги.', 'Сложно', 'Ёшкин кот', 'Ёшкин кот|ёшкин кот|Ешкин кот|ешкин кот');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (30, 500, 'Чтобы качественно СДЕЛАТЬ ЭТО, на тематических форумах предлагают «Р-88», «Наирит» или «Радикал».', 'Сложно', 'Склеить ласты', 'Склеить ласты|склеить ласты');

        -- ==========================================
        -- Тема 31: Вечная
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (31, 'Вечная');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (31, 100, 'Как известно, Французская Академия Наук не занимается изобретением ЭТОГО.', 'Легко', 'Вечного двигателя', 'Вечного двигателя|вечного двигателя|Вечный двигатель|вечный двигатель|Двигателя вечного|двигателя вечного');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (31, 200, '«Он как душа — неразделим и вечен», — писал Пушкин об ЭТОМ союзе.', 'Легко', 'Союз друзей', 'Союз друзей|союз друзей|Дружеский союз|дружеский союз|союзе друзей|Союзе друзей');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (31, 300, 'Многолетняя криолитозОна называется ещё и ТАК.', 'Средне', 'Вечная мерзлота', 'Вечная мерзлота|вечная мерзлота|Мерзлота|мерзлота|Мерзлота вечная|мерзлота вечная');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (31, 400, 'По словам О. Бендера, Вечный Жид «бывал везде: и на Рейне, и на Ганге, и на Миссисипи, и на Ян-Цзы, и на НИгере, и на Волге. И не был он только ТАМ». Путешествие ТУДА оказалось роковым.', 'Сложно', 'На Днепр', 'На Днепр|на Днепр|на днепр|Днепр|днепр|На Днепре|на Днепре|на днепре');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (31, 500, 'К НИМ относятся и Дон Жуан, и Дон Кихот.', 'Сложно', 'Вечные образы', 'Вечные образы|вечные образы|Вечный образ|вечный образ');

        -- ==========================================
        -- Тема 32: Вопросы
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (32, 'Вопросы');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (32, 100, 'ТАКОЙ вопрос не требует ответа.', 'Легко', 'Риторический', 'Риторический|риторический|Риторический вопрос|риторический вопрос');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (32, 200, 'Именно ЭТОТ вопрос, согласно Булгакову, испортил москвичей.', 'Легко', 'Квартирный', 'Квартирный|квартирный|Квартирный вопрос|квартирный вопрос');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (32, 300, 'По правилам пунктуации ЭТОГО языка, знак вопроса ставится не только в конце, но и в начале вопросительного предложения.', 'Средне', 'Испанский', 'Испанский|испанский|Испанский язык|испанский язык|Испанского|испанского|Испанского языка|испанского языка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (32, 400, 'ЭТИМ вопросом заканчивается пушкинская «Русалочка».', 'Сложно', '«Откуда ты, прекрасное дитя?»', '«Откуда ты, прекрасное дитя?»|"Откуда ты, прекрасное дитя?"|«откуда ты, прекрасное дитя?»|"откуда ты, прекрасное дитя?"|Откуда ты, прекрасное дитя?|откуда ты, прекрасное дитя?|Откуда ты прекрасное дитя|откуда ты прекрасное дитя');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (32, 500, 'Из ЭТОЙ статьи Ленина мы узнали мудрую мысль о том, что «надо мечтать».', 'Сложно', '«Что делать?»', '«Что делать?»|"Что делать?"|«что делать?»|"что делать?"|Что делать?|что делать?|«Что делать»|"Что делать"|Что делать|что делать');

        -- ==========================================
        -- Тема 33: Матрица «…ИЗИ…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (33, 'Матрица «…ИЗИ…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (33, 100, 'Во всём мире его называют кубинским, а у нас...', 'Легко', 'Карибский кризис', 'Карибский кризис|карибский кризис|Карибским кризисом|карибским кризисом|Кризис карибский|кризис карибский');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (33, 200, 'Говорят, однажды он перехитрил смерть.', 'Легко', 'Сизиф', 'Сизиф|сизиф');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (33, 300, 'Так по-испански звучит слово «расследование».', 'Средне', 'Инквизиция', 'Инквизиция|инквизиция');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (33, 400, 'Это не только карточка, но и вид сюртука.', 'Сложно', 'Визитка', 'Визитка|визитка|Визитная карточка|визитная карточка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (33, 500, 'ЭТОТ термин произошел от английского слова, означающего «аренда».', 'Сложно', 'Лизинг', 'Лизинг|лизинг');

        -- ==========================================
        -- Тема 34: Архитектура
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (34, 'Архитектура');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (34, 100, 'В Древней Греции ИХ было 7 типов: 1) в Антах, 2) прОстиль, 3) амфипрОстиль, 4) перИптер, 5) дИптер, 6) псевдодИптер, 7) тОлос.', 'Легко', 'Храмы', 'Храмы|храмы|Храм|храм');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (34, 200, 'ТАК в Древней Греции назывался храм всех богов.', 'Легко', 'Пантеон', 'Пантеон|пантеон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (34, 300, 'ЭТА водонапорная башня известного инженера была построена в Борисове в 1927 году, а подобных сооружений в мире насчитывается всего 11 шт.', 'Средне', 'Шуховская башня', 'Шуховская башня|шуховская башня|Башня Шухова|башня Шухова|башня шухова');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (34, 400, 'Во вьетнамской ранней архитектуре широко использовались 2 вида естественных стройматериалов: первый — устойчивое против гниения железное дерево, а ВТОРОЙ?', 'Сложно', 'Бамбук', 'Бамбук|бамбук');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (34, 500, 'ТАК в Древней Греции называлась площадь, где обсуждались важнейшие городские дела, совершались торговые сделки.', 'Сложно', 'Агора', 'Агора|агора');

        -- ==========================================
        -- Тема 35: Матрица «…АД…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (35, 'Матрица «…АД…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (35, 100, 'У славян ЭТО слово означало «согласие», «мир», «стройность», «порядок».', 'Легко', 'Лад', 'Лад|лад');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (35, 200, 'Именно ТАК называется опись земельных участков.', 'Легко', 'Кадастр', 'Кадастр|кадастр');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (35, 300, 'ЭТА латинская приставка имеет значения «к, при, возле» и многие другие.', 'Средне', 'Ad', 'Ad|ad|Ад|ад');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (35, 400, 'Именно ТАК называется ярый приверженец какого-либо учения, идеи.', 'Сложно', 'Адепт', 'Адепт|адепт');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (35, 500, 'ЭТО самый разрушительный вид осадков.', 'Сложно', 'Град', 'Град|град');

        -- ==========================================
        -- Тема 36: Матрица «…НЕТ…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (36, 'Матрица «…НЕТ…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (36, 100, 'Инспекторы ГАИ имеют право задержать водителя по подозрению в нахождении именно в ЭТОМ состоянии.', 'Легко', 'Нетрезвом', 'Нетрезвом|нетрезвом|Нетрезвом состоянии|нетрезвом состоянии|Нетрезвый|нетрезвый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (36, 200, 'ЭТО чистая масса товара, продукта или сырья без учета тары, упаковки, контейнера или поддонов.', 'Легко', 'Нетто', 'Нетто|нетто');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (36, 300, 'Именно ТАКОЙ титул носил британский сэр Генри Баскервиль.', 'Средне', 'Баронет', 'Баронет|баронет');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (36, 400, 'Именно ТАК называется детская обувь для самых маленьких.', 'Сложно', 'Пинетки', 'Пинетки|пинетки|Пинетка|пинетка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (36, 500, 'ТАК на Руси называли летучую мышь.', 'Сложно', 'Нетопырь', 'Нетопырь|нетопырь');

        -- ==========================================
        -- Тема 37: Две буквы
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (37, 'Две буквы');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (37, 100, 'Ню, начнём. КАК называется искусство обнажённого тела?', 'Легко', 'Ню', 'Ню|ню');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (37, 200, 'ЕГО нейтральное значение равно 7, от 1 до 6 говорит о кислотности среды, от 8 до 14 — о щёлочности.', 'Легко', 'pH-фактор', 'pH-фактор|pH фактор|ph-фактор|ph фактор|pH|ph|Рш-фактор|рш-фактор');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (37, 300, 'ЭТОТ адрес пока ещё состоит из четырёх октЕтов и необходим каждому, кто пользуется Интернетом.', 'Средне', 'IP-адрес', 'IP-адрес|ip-адрес|IP адрес|ip адрес|IP|ip|Айпи-адрес|айпи-адрес|Айпи|айпи');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (37, 400, 'ЭТИ две буквы располагались в самом верху советской таблицы для проверки зрения.', 'Сложно', 'Ш и Б', 'Ш и Б|ш и б|Ш Б|ш б|Ш, Б|ш, б|ШБ|шб');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (37, 500, 'ЭТО и истребитель, и монета.', 'Сложно', 'Су', 'Су|су');

        -- ==========================================
        -- Тема 38: Куклы
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (38, 'Куклы');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (38, 100, 'ТАК в средневековье назывались фигурки, изображавшие в кукольных представлениях Деву Марию.', 'Легко', 'Марионетка', 'Марионетка|марионетка|Марионетки|марионетки');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (38, 200, 'ТАК звали рыжеволосую куклу в комбинезоне, в которую вселилась душа серийного убийцы Чарльза Ли Рэя.', 'Легко', 'Чаки', 'Чаки|чаки');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (38, 300, 'ЭТА группа выпустила в 1986 году альбом, название которого переводится как «Кукловод».', 'Средне', 'Металлика', 'Металлика|металлика|Metallica|metallica');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (38, 400, 'ЕЁ прародителем был старичок ДарУму.', 'Сложно', 'Матрёшка', 'Матрёшка|матрёшка|Матрешка|матрешка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (38, 500, 'Ежегодно в ЭТОЙ азиатской стране 3 марта проводится «Фестиваль кукол».', 'Сложно', 'Япония', 'Япония|япония|Японии|японии|В Японии|в Японии|в японии');

        -- ==========================================
        -- Тема 39: Пословицы и поговорки
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (39, 'Пословицы и поговорки');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (39, 100, 'Именно ТОГДА, согласно русской пословице, лиса кур считает.', 'Легко', 'Во сне', 'Во сне|во сне|Сон|сон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (39, 200, 'Именно ЭТО, согласно русской пословице, нельзя нашить на чужой рот.', 'Легко', 'Пуговицу', 'Пуговицу|пуговицу|Пуговица|пуговица');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (39, 300, 'Именно ТОГДА, согласно осетинской пословице, медведь заявил, что мёд горек.', 'Средне', 'Когда наелся', 'Когда наелся|когда наелся|Наелся|наелся');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (39, 400, 'Греческая пословица «пить по-скифски» означала именно ЭТО.', 'Сложно', 'Упиваться до смерти', 'Упиваться до смерти|упиваться до смерти|Пить не разбавляя|пить не разбавляя|Не разбавлять вино водой|не разбавлять вино водой');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (39, 500, 'Именно на ЭТОТ вопрос, согласно турецкой поговорке, осёл отвечает, что его мать лошадь.', 'Сложно', '«Кто твой отец?»', '«Кто твой отец?»|"Кто твой отец?"|«кто твой отец?»|"кто твой отец?"|Кто твой отец?|кто твой отец?|Твой отец кто|твой отец кто');

        -- ==========================================
        -- Тема 40: Мозги
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (40, 'Мозги');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (40, 100, 'Именно ЭТО было заменителем мозгов у Винни-Пуха.', 'Легко', 'Опилки', 'Опилки|опилки');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (40, 200, 'Название ЭТОЙ игры можно перевести и как «перстневой мозг».', 'Легко', 'Брейн-ринг', 'Брейн-ринг|брейн-ринг|Брейн ринг|брейн ринг');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (40, 300, 'По мнению Игоря Губермана, ЭТО — единственная кость, лишённая какого-либо мозга.', 'Средне', 'Ребро', 'Ребро|ребро');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (40, 400, 'Именно у ЭТОГО примата масса мозга больше массы мозга некоторых людей.', 'Сложно', 'Горилла', 'Горилла|горилла');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (40, 500, 'Основная функция ЭТОГО мозга — информационно-транспортная.', 'Сложно', 'Продолговатый', 'Продолговатый|продолговатый|Продолговатый мозг|продолговатый мозг');

        -- ==========================================
        -- Тема 41: Пригодится в быту
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (41, 'Пригодится в быту');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (41, 100, 'Некоторые многоразовые ИХ разновидности комплектовались счетчиками по номиналам, другие имели музыкальные замки, третьи открывались только по достижении определенной суммы.', 'Легко', 'Копилки', 'Копилки|копилки|Копилка|копилка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (41, 200, 'В городе Мейкон женщина отбилась от грабителя с помощью ЭТОГО бытового УСТРОЙСТВА. Он, правда, был выключен, и ожогов не осталось.', 'Легко', 'Утюг', 'Утюг|утюг');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (41, 300, 'В городе Линкольн мужчина ограбил хозяйственный магазин, использовав для маскировки ЕЕ. Сколько метров ЕЕ было использовано, не уточняется.', 'Средне', 'Туалетная бумага', 'Туалетная бумага|туалетная бумага|Рулон туалетной бумаги|рулон туалетной бумаги');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (41, 400, 'Внутри стержня особой ЕГО разновидности находится полый канал с клапаном для отвода двуокиси углерода.', 'Сложно', 'Штопор', 'Штопор|штопор');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (41, 500, 'ЕГО название происходит от немецкого «пробивать насквозь».', 'Сложно', 'Дуршлаг', 'Дуршлаг|дуршлаг|Друшлаг|друшлаг');

        -- ==========================================
        -- Тема 42: Супергерои
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (42, 'Супергерои');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (42, 100, 'Эрик Брукс — мастерски владеющий мечом охотник на вампиров — известен под ЭТИМ ПРОЗВИЩЕМ.', 'Легко', 'Блейд', 'Блейд|блейд|Blade|blade');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (42, 200, 'ТАК звали персонажа «Людей Икс», который обладает способностью создавать сверхзвуковые волны любой длины.', 'Легко', 'Банши', 'Банши|банши|Баньши|баньши');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (42, 300, 'ЭТОТ невероятно сильный БУГАЙ в мире был доктором Брюсом Баннером.', 'Средне', 'Халк', 'Халк|халк');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (42, 400, 'ЭТИ французские герои, обладающие силой созидания и разрушения, используют для превращения талисманы.', 'Сложно', 'Леди Баг и Супер Кот (Кот Нуар)', 'Леди Баг и Супер Кот|леди баг и супер кот|Леди Баг и Кот Нуар|леди баг и кот нуар|Леди Баг|леди баг');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (42, 500, 'Изначально ЭТОТ ПЕРСОНАЖ был врагом Человека-паука, но впоследствии встал на его сторону. Для боя обычно превращал руки в булавы или молоты, а вот усыплять врагов не умел.', 'Сложно', 'Песочный человек', 'Песочный человек|песочный человек|Сэндмен|сэндмен|Sandman|sandman');

        -- ==========================================
        -- Тема 43: Ягоды, фрукты, овощи
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (43, 'Ягоды, фрукты, овощи');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (43, 100, 'В своем стихотворении Александр КУшнер называет ИХ «зелеными тиграми».', 'Легко', 'Арбузы', 'Арбузы|арбузы|Арбуз|арбуз');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (43, 200, 'С НЕЙ сравнивается обманчиво красивая жизнь на чужбине, оборачивающаяся горькой неволей.', 'Легко', 'Калина', 'Калина|калина');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (43, 300, 'В Армении на свадьбе принято разбивать ЕГО о стену — чем сильнее рассыплется от удара, тем больше родится детей.', 'Средне', 'Гранат', 'Гранат|гранат');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (43, 400, 'У инков одним из способов оценки времени было соотнесение с затратами на ЕГО варку.', 'Сложно', 'Картофель', 'Картофель|картофель|Картошка|картошка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (43, 500, 'ЭТО экзотический плод вьющихся кактусов с яркой кожурой и мягкой мякотью, напоминающей по вкусу смесь киви, груши и арбуза.', 'Сложно', 'Питахайя (питайя, драгонфрут)', 'Питахайя|питахайя|Питайя|питайя|Драгонфрут|драгонфрут|Драконий фрукт|драконий фрукт');

        -- ==========================================
        -- Тема 44: Сумки
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (44, 'Сумки');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (44, 100, 'Во времена дефицита в Советском Союзе люди носили ЕЕ с собой на случай — вдруг удастся что-то купить.', 'Легко', 'Авоська', 'Авоська|авоська');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (44, 200, 'ЕГО название в переводе с французского языка означает «дорожная сумка».', 'Легко', 'Саквояж', 'Саквояж|саквояж');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (44, 300, 'Название ЭТИХ СУМОЧЕК происходит от латинского «сетка». Хотя прозвали их «смехотворными».', 'Средне', 'Ридикюль', 'Ридикюль|ридикюль');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (44, 400, 'На Руси ТАК называли вора, срезающего кошельки с пояса.', 'Сложно', 'Мошенник', 'Мошенник|мошенник|Карманник|карманник');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (44, 500, 'Свое название ЭТОТ ТИП рюкзака получил за свою форму в виде шара.', 'Сложно', 'Колобок', 'Колобок|колобок');

        -- ==========================================
        -- Тема 45: Языки
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (45, 'Языки');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (45, 100, 'ЭТОТ ЯЗЫК программирования получил свое название в честь английских комиков.', 'Легко', 'Python', 'Python|python|Питон|питон|Пайтон|пайтон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (45, 200, 'Немка Мария ГАнкель считается первой поэтессой, которая писала на ЭТОМ международном ЯЗЫКЕ как основном. Не беда, что выучила она его только в возрасте 61 года.', 'Легко', 'Эсперанто', 'Эсперанто|эсперанто');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (45, 300, 'Система визуальных знаков, которую часто ошибочно считают просто пантомимой, хотя она имеет свою грамматику и лексику.', 'Средне', 'Язык жестов', 'Язык жестов|язык жестов|Жестовый язык|жестовый язык');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (45, 400, 'На языке цветов именно ТАКАЯ роза символизирует любовь с первого взгляда.', 'Сложно', 'Без шипов', 'Без шипов|без шипов|Роза без шипов|роза без шипов');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (45, 500, 'В 15 лет этот человек, потерявший зрение в детстве, разработал рельефно-точечный метод чтения, который используется незрячими людьми по всему миру до сих пор.', 'Сложно', 'Шрифт (азбука) Брайля', 'Шрифт Брайля|шрифт Брайля|шрифт брайля|Азбука Брайля|азбука Брайля|азбука брайля|Брайль|брайль|Луи Брайль|луи брайль');

        -- ==========================================
        -- Тема 46: Закон есть закон
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (46, 'Закон есть закон');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (46, 100, 'На тело, погруженное в жидкость (или газ), действует выталкивающая сила, равная весу вытесненной этим телом жидкости.', 'Легко', 'Закон Архимеда', 'Закон Архимеда|закон Архимеда|закон архимеда|Архимеда|архимеда|Архимед|архимед');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (46, 200, 'Сила взаимодействия двух точечных неподвижных заряженных тел в вакууме направлена вдоль прямой, соединяющей заряды, прямо пропорциональна произведению модулей зарядов и обратно пропорциональна квадрату расстояния между ними.', 'Легко', 'Закон Кулона', 'Закон Кулона|закон Кулона|закон кулона|Кулона|кулона|Кулон|кулон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (46, 300, 'В равных объемах различных газов, взятых при одинаковых температуре и давлении, содержится одно и то же число молекул.', 'Средне', 'Закон Авогадро', 'Закон Авогадро|закон Авогадро|закон авогадро|Авогадро|авогадро');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (46, 400, 'Всё, что может пойти не так, пойдёт не так.', 'Сложно', 'Закон Мёрфи (закон подлости)', 'Закон Мёрфи|закон Мёрфи|закон мёрфи|Закон Мерфи|закон мерфи|Закон подлости|закон подлости|Мёрфи|мёрфи|Мерфи|мерфи');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (46, 500, 'Эмпирический закон, связывающий красное смещение галактик и расстояние до них линейным образом. Установлен экспериментально с помощью телескопа в 1929 году.', 'Сложно', 'Закон Хаббла', 'Закон Хаббла|закон Хаббла|закон хаббла|Хаббла|хаббла|Хаббл|хаббл');

        -- ==========================================
        -- Тема 47: Нечисть
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (47, 'Нечисть');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (47, 100, 'В русском фольклоре ОНА также именуется купАлкой, лоскотУхой или водянИцей.', 'Легко', 'Русалка', 'Русалка|русалка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (47, 200, 'В средневековых европейских легендах ОНИ часто похищали принцесс и охраняли золото в пещерах.', 'Легко', 'Драконы', 'Драконы|драконы|Дракон|дракон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (47, 300, 'В мультсериале «Каспер. Школа страха» главный герой слишком дружелюбный, поэтому не может пугать людей. Кем ОН является по существу?', 'Средне', 'Привидением (призраком)', 'Привидением|привидением|Привидение|привидение|Призраком|призраком|Призрак|призрак|Духом|духом|Дух|дух');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (47, 400, 'Согласно некоторым ученым, в ЭТОМ «ЗАЛЕСЬЕ» была наиболее распространена порфирия.', 'Сложно', 'Трансильвания', 'Трансильвания|трансильвания|В Трансильвании|в Трансильвании|в трансильвании');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (47, 500, 'ТАК называется оборотень-лисица в японской мифологии.', 'Сложно', 'Кицунэ', 'Кицунэ|кицунэ|Кицуне|кицуне');

        -- ==========================================
        -- Тема 48: Головы
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (48, 'Головы');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (48, 100, 'ЭТО человек, отлавливающий преступников и дезертиров за вознаграждение.', 'Легко', 'Охотник за головами', 'Охотник за головами|охотник за головами|Охотники за головами|охотники за головами|Bounty hunter|bounty hunter');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (48, 200, 'Назовите ЛЮБОЕ из животных, умеющих поворачивать голову на 270 градусов.', 'Легко', 'Сова (филин)', 'Сова|сова|Филин|филин|Совы|совы|Филины|филины');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (48, 300, 'Как звучит второе имя (прозвище) главного героя мультсериала «Кик Бутовский», которого постоянно тянет на безумные трюки?', 'Средне', 'Сорвиголова', 'Сорвиголова|сорвиголова');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (48, 400, 'ТАК называют технику фотографирования с фокусировкой на лице. В шУтерах ОН обычно смертелен.', 'Сложно', 'Head shot (Хедшот)', 'Head shot|head shot|Headshot|headshot|Хедшот|хедшот|Хэдшот|хэдшот');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (48, 500, 'В названии этого приключенческого романа Майн Рида фигурирует призрак, который на деле оказывается трупом Генри Пойндекстера, привязанным к лошади. Назовите этот роман.', 'Сложно', '«Всадник без головы»', '«Всадник без головы»|"Всадник без головы"|«всадник без головы»|"всадник без головы"|Всадник без головы|всадник без головы');

-- =    =========================================
        -- Тема 49: Матрица «…ЦЕНТ…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (49, 'Матрица «…ЦЕНТ…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (49, 100, 'ЭТО ближайшая к Солнцу звезда.', 'Легко', 'Проксима Центавра', 'Проксима Центавра|проксима центавра|Центавра|центавра|Проксима|проксима');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (49, 200, 'Обладатель ЭТОЙ степени не обладал большим интеллектом.', 'Легко', 'Доцент', 'Доцент|доцент');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (49, 300, 'Сто катренов у Нострадамуса составляют...', 'Средне', 'Центурию', 'Центурию|центурию|Центурия|центурия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (49, 400, 'Знак ударения называют ещё и ТАК.', 'Сложно', 'Акцент', 'Акцент|акцент');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (49, 500, 'Вместе с НЕЙ погибла и ее сестра — Лиза.', 'Сложно', 'Старуха-процентщица', 'Старуха-процентщица|старуха-процентщица|Процентщица|процентщица');

        -- ==========================================
        -- Тема 50: В переводе
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (50, 'В переводе');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (50, 100, 'Судя по названию, с помощью ЭТОГО прибора древние греки хватали с неба звёзды.', 'Легко', 'Астролябия', 'Астролябия|астролябия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (50, 200, 'Переведите число 100 000 из двоичной системы в шестнадцатеричную.', 'Легко', '20', '20|двадцать|Двадцать');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (50, 300, 'Есть что-то странное в ЭТОМ архитектурном стиле.', 'Средне', 'Барокко', 'Барокко|барокко');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (50, 400, 'Название ЭТОЙ металл-группы означает «могила», в переводе с португальского.', 'Сложно', 'Сепультура', 'Сепультура|сепультура|Sepultura|sepultura');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (50, 500, 'По-латыни «старик» — «senex», а по-арабски...', 'Сложно', 'Шейх', 'Шейх|шейх');

        -- ==========================================
        -- Тема 51: Ответьте в рифму
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (51, 'Ответьте в рифму');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (51, 100, 'ГДЕ в 1941 году А.Г. Стаханов возглавил шахту №31?', 'Легко', 'В Караганде', 'В Караганде|в Караганде|в караганде|Караганда|караганда');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (51, 200, 'ОТКУДА был сделан заказ на поставку партии шоколада для подрастающего поколения?', 'Легко', 'От верблюда', 'От верблюда|от верблюда|Верблюд|верблюд');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (51, 300, 'КОГДА, согласно гимну КПБ, право владеть землёй получат паразиты?', 'Средне', 'Никогда', 'Никогда|никогда');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (51, 400, 'КТО в 1928 году написал пьесу «Орфей», а в 1950 снял фильм с таким же названием?', 'Сложно', 'Жан Кокто', 'Жан Кокто|жан кокто|Кокто|кокто');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (51, 500, 'ПОЧЕМУ один из альбомов получил ТАКОЕ название можно понять, если вспомнить фамилию автора-исполнителя.', 'Сложно', '«... по Качану!»', 'По Качану|по Качану|по качану|По качану');

        -- ==========================================
        -- Тема 52: Домино
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (52, 'Домино');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (52, 100, 'Изобретение домино, по одной из версий, приписывается монахам ЭТОГО ордена.', 'Легко', 'Доминиканского', 'Доминиканского|доминиканского|Доминиканский|доминиканский|Доминиканцы|доминиканцы');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (52, 200, 'Именно ЭТО игроки в домино называют азом.', 'Легко', 'Костяшку с одним очком', 'Костяшку с одним очком|костяшку с одним очком|С одним очком|с одним очком|Единица|единица');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (52, 300, 'Именно столько костяшек в домино.', 'Средне', '28', '28|двадцать восемь|Двадцать восемь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (52, 400, 'Именно с ЭТОЙ планеты была родом фея Блум.', 'Сложно', 'Домино', 'Домино|домино');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (52, 500, 'ТАК называется крупнейшая международная сеть пиццерий, основанная в 1960 году в США.', 'Сложно', 'Domino’s Pizza', 'Domino’s Pizza|domino’s pizza|Dominos Pizza|dominos pizza|Доминос|доминос|Доминос пицца|доминос пицца');

        -- ==========================================
        -- Тема 53: Матрица «…ВЫЙ…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (53, 'Матрица «…ВЫЙ…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (53, 100, 'ЭТОТ цвет в радуге — последний.', 'Легко', 'Фиолетовый', 'Фиолетовый|фиолетовый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (53, 200, 'Название ЭТОГО цвета произошло от апельсина.', 'Легко', 'Оранжевый', 'Оранжевый|оранжевый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (53, 300, 'ЭТО одно из многих прозвищ дьявола.', 'Средне', 'Лукавый', 'Лукавый|лукавый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (53, 400, 'ЭТИМ цветом пышно расцветают разные нехорошие явления.', 'Сложно', 'Махровый', 'Махровый|махровый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (53, 500, 'ТАК называли на Руси ромбической формы нашивку на спинах у каторжан.', 'Сложно', 'Бубновый туз', 'Бубновый туз|бубновый туз|Туз бубей|туз бубей');

        -- ==========================================
        -- Тема 54: Древняя Греция
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (54, 'Древняя Греция');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (54, 100, 'Именно ТАК в Древней Греции именовался пергамент, сложенный ради удобства пользования вчетверо.', 'Легко', 'Тетрадь', 'Тетрадь|тетрадь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (54, 200, 'В честь олимпиоников слагали эпиникии, в честь Аполлона — пеаны, а КАК назывались посвящённые Дионису?', 'Легко', 'Дифирамбы', 'Дифирамбы|дифирамбы|Дифирамб|дифирамб');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (54, 300, 'ИХ насчитывалось около 16-ти, однако самой известной была ТА, что лежала между Фессалией и Македонией. Назовите ЕЁ.', 'Средне', 'Олимп', 'Олимп|олимп|Гора Олимп|гора олимп');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (54, 400, 'Если вы знаете, как по-гречески «владыка земли», то назовете ИМЯ старшего сына Кроноса, которого Гомер назвал «синекудрым».', 'Сложно', 'Посейдон', 'Посейдон|посейдон');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (54, 500, 'Именно ТАК звали служанку, которая смогла рассмешить Деметру, а древние греки назвали ЕЁ именем стихи.', 'Сложно', 'Ямб', 'Ямб|ямб');

        -- ==========================================
        -- Тема 55: Прозвища
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (55, 'Прозвища');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (55, 100, 'ЭТОТ монарх удостоился своего прозвища за Ходынку и Кровавое воскресение.', 'Легко', 'Николай II', 'Николай II|николай 2|Николай 2|Николай Второй|николай второй|Николай Кровавый|николай кровавый');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (55, 200, 'ЭТОГО девятого номера называют «Зубастиком».', 'Легко', 'Роналдо', 'Роналдо|роналдо');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (55, 300, 'ОН обрёл своё прозвище после 15 июля 1240 года.', 'Средне', 'Александр Невский', 'Александр Невский|александр невский|Невский|невский');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (55, 400, 'Именно ЭТО прозвище носил тот, при ком империя Османов достигла наивысшего расцвета в середине 16 века.', 'Сложно', 'Сулейман Великолепный', 'Сулейман Великолепный|сулейман великолепный|Сулейман|сулейман|Великолепный|великолепный');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (55, 500, 'ЭТИМ прозвищем многие белорусы называют президента.', 'Сложно', 'Батька', 'Батька|батька');

        -- ==========================================
        -- Тема 56: Анатомия
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (56, 'Анатомия');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (56, 100, 'В НЕЙ находятся голосовые связки.', 'Легко', 'Гортань', 'Гортань|гортань');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (56, 200, 'ОН имеет 3 оболочки: твёрдую, мягкую и паутинную.', 'Легко', 'Мозг', 'Мозг|мозг|Головной мозг|головной мозг');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (56, 300, 'ЭТОТ мышечный орган из-за особенности расположения волокон никогда не устаёт.', 'Средне', 'Язык', 'Язык|язык');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (56, 400, 'Сколько позвонков в грудном отделе позвоночника человека?', 'Сложно', '12', '12|двенадцать|Двенадцать');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (56, 500, 'Генетическое заболевание трисомия-21 носит ЕГО имя.', 'Сложно', 'Даун', 'Даун|даун|Синдром Дауна|синдром Дауна|синдром дауна|Джона Лэнгдона Дауна|джона лэнгдона дауна');

        -- ==========================================
        -- Тема 57: Меры
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (57, 'Меры');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (57, 100, 'Если ОНА короткая, то равна 907 кг, если длинная — 1016 кг.', 'Легко', 'Тонна', 'Тонна|тонна');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (57, 200, 'Основная мера жидкости на Руси, равная 490 литров, называлась именно ТАК.', 'Легко', 'Бочка', 'Бочка|бочка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (57, 300, 'Четыре вершка составляют одну...', 'Средне', 'Пядь', 'Пядь|пядь');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (57, 400, 'Именно ТАК называется 1/100 дюйма.', 'Сложно', 'Калибр', 'Калибр|калибр');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (57, 500, 'ЭТА русская мера составляет 1/16 ведра.', 'Сложно', 'Винная бутылка', 'Винная бутылка|винная бутылка|Бутылка|бутылка');

        -- ==========================================
        -- Тема 58: Матрица «…ТРАНС…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (58, 'Матрица «…ТРАНС…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (58, 100, 'Скажите на латыни «пересаживание».', 'Легко', 'Трансплантация', 'Трансплантация|трансплантация');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (58, 200, 'ОНА передаёт вращение от двигателя к рабочим машинам.', 'Легко', 'Трансмиссия', 'Трансмиссия|трансмиссия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (58, 300, 'ЭТО приспособление для построения и измерения углов на чертежах известно нам со школьной скамьи.', 'Средне', 'Транспортир', 'Транспортир|транспортир');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (58, 400, 'Замена строк столбцами приводит к получению именно ТАКОЙ матрицы.', 'Сложно', 'Транспонированной', 'Транспонированной|транспонированной|Транспонированная|транспонированная');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (58, 500, 'Именно ТАК расшифровывается аббревиатура ТНК.', 'Сложно', 'Транснациональная корпорация', 'Транснациональная корпорация|транснациональная корпорация');

        -- ==========================================
        -- Тема 59: Букашки
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (59, 'Букашки');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (59, 100, 'Вопреки распространенному мнению родиной ЭТОГО жука являются северные районы Мексики.', 'Легко', 'Колорадский жук', 'Колорадский жук|колорадский жук|Колорадский|колорадский');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (59, 200, 'Именно ТАК называется дом для лесных пчел.', 'Легко', 'Борть', 'Борть|борть');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (59, 300, 'Именно ЭТО насекомое, согласно русскому фольклору, у нищего в кармане на аркане.', 'Средне', 'Вошь', 'Вошь|вошь|Вши|вши');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (59, 400, 'Именно ЭТОМУ насекомому нужен литр цветочного нектара, чтобы пролететь 150 млн км.', 'Сложно', 'Комару', 'Комару|комару|Комар|комар');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (59, 500, 'В древней Руси именно ЕГО называли изОком.', 'Сложно', 'Сверчка', 'Сверчка|сверчка|Сверчок|сверчок');

        -- ==========================================
        -- Тема 60: Сколько?
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (60, 'Сколько?');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (60, 100, 'Сколько дней в невисокосном году?', 'Легко', '365', '365|триста шестьдесят пять|Триста шестьдесят пять');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (60, 200, 'Одним из подвигов Геракла было усмирение пса Цербера. Сколько у Цербера было голов?', 'Легко', '3', '3|три|Три');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (60, 300, 'Сколько максимум зубов может быть у человека?', 'Средне', '32', '32|тридцать два|Тридцать два');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (60, 400, 'Сколько строк содержит классический сонет?', 'Сложно', '14', '14|четырнадцать|Четырнадцать');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (60, 500, 'Сколько нулей в числе ГугОл?', 'Сложно', '100', '100|сто|Сто');

        -- ==========================================
        -- Тема 61: Дары моря
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (61, 'Дары моря');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (61, 100, 'КАКОГО цвета кровь у осьминога?', 'Легко', 'Голубая', 'Голубая|голубая|Голубого|голубого');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (61, 200, 'ЭТА смертельно ядовитая рыба — лакомое блюдо у японцев.', 'Легко', 'Фугу', 'Фугу|фугу|Рыба фугу|рыба фугу');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (61, 300, 'Каждый может услышать «шум моря» через НЕЁ.', 'Средне', 'Ракушка', 'Ракушка|ракушка|Раковина|раковина|Раковину|раковину|Морская раковина|морская раковина');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (61, 400, 'По словам деда Щукаря, в общем котле сварилась не лягушка, а...', 'Сложно', 'Устрица', 'Устрица|устрица');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (61, 500, 'ЭТА одноклеточная водоросль широко используется для очистки воздуха в космических кораблях.', 'Сложно', 'Хлорелла', 'Хлорелла|хлорелла');

        -- ==========================================
        -- Тема 62: Вертикальная
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (62, 'Вертикальная');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (62, 100, 'Горизонтальная составляющая матрицы — это строка, а вертикальная?', 'Легко', 'Столбец', 'Столбец|столбец|Колонка|колонка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (62, 200, 'Именно ЭТО свойство вертикальных углов отмечает геометрия.', 'Легко', 'Их равенство', 'Их равенство|их равенство|Равенство|равенство|Они равны|они равны|Равны|равны');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (62, 300, 'В компьютерных редакторах горизонтальная ориентация листа бумаги называется альбомной, а вертикальная?', 'Средне', 'Книжной', 'Книжной|книжной|Книжная|книжная|Портретной|портретной|Портретная|портретная');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (62, 400, 'В декартовой системе координат по горизонтали расположены абсцисса и ордината, а по вертикали…', 'Сложно', 'Аппликата', 'Аппликата|аппликата|Ось аппликат|ось аппликат');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (62, 500, 'Именно ТАК называется большой круг небесной сферы, проходящий через зенит и надир.', 'Сложно', 'Вертикал', 'Вертикал|вертикал');

        -- ==========================================
        -- Тема 63: Матрица «…ИЛИ…»
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (63, 'Матрица «…ИЛИ…»');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (63, 100, 'ЭТИ люди шли к святым местам.', 'Легко', 'Пилигримы', 'Пилигримы|пилигримы|Пилигрим|пилигрим');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (63, 200, 'ЭТО протянулось почти на 5 тысяч километров вдоль западного побережья Южной Америки.', 'Легко', 'Чили', 'Чили|чили');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (63, 300, 'ЭТО приходит дважды в сутки на побережье всех морей.', 'Средне', 'Прилив', 'Прилив|прилив');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (63, 400, 'ЭТОТ архипелаг, ныне независимое государство, открывшие ЕГО испанцы назвали в честь своего короля.', 'Сложно', 'Филиппины', 'Филиппины|филиппины');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (63, 500, 'ЭТО был первый вид общественного транспорта.', 'Сложно', 'Дилижанс', 'Дилижанс|дилижанс');

        -- ==========================================
        -- Тема 64: Болезни
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (64, 'Болезни');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (64, 100, 'Именно ТАК называются приступы удушья вследствие сужения просвета бронхов.', 'Легко', 'Астма', 'Астма|астма|Бронхиальная астма|бронхиальная астма');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (64, 200, 'Именно ТАК называется заболевание, вызванное повышенной чувствительностью организма к какому-либо определённому веществу.', 'Легко', 'Аллергия', 'Аллергия|аллергия');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (64, 300, 'Именно ТАК называется наука, изучающая воздействие лекарств на живые организмы.', 'Средне', 'Фармакология', 'Фармакология|фармакология');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (64, 400, 'Именно ТАК называется ограниченное скопление крови при закрытых повреждениях, сопровождающихся кровоизлияниями.', 'Сложно', 'Гематома', 'Гематома|гематома|Синяк|синяк');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (64, 500, 'Именно ТАК по-русски звучит название гиперметропии.', 'Сложно', 'Дальнозоркость', 'Дальнозоркость|дальнозоркость');

        -- ==========================================
        -- Тема 65: Белая
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (65, 'Белая');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (65, 100, 'Именно ТАК зачастую называют Зимние Олимпийские Игры.', 'Легко', 'Белая Олимпиада', 'Белая Олимпиада|белая олимпиада|Белая олимпиада');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (65, 200, 'В Санкт-Петербурге ЭТО продолжается с 11 июня по 2 июля.', 'Легко', 'Белые ночи', 'Белые ночи|белые ночи');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (65, 300, 'Часто ОН — пятистопный ямб.', 'Средне', 'Белый стих', 'Белый стих|белый стих');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (65, 400, 'Именно СТОЛЬКО белых клавиш на фортепиано.', 'Сложно', '52', '52|пятьдесят два|Пятьдесят два');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (65, 500, 'Именно ТАК называются очень плотные горячие звёзды малых размеров из вырожденного газа.', 'Сложно', 'Белые карлики', 'Белые карлики|белые карлики|Белый карлик|белый карлик');

        -- ==========================================
        -- Тема 66: Кругом вода
        -- ==========================================
        INSERT OR IGNORE INTO categories (id, name) VALUES (66, 'Кругом вода');
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (66, 100, 'Именно ТАК называли человека, бегающего за всеми в догонялках.', 'Легко', 'Вода', 'Вода|вода');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (66, 200, 'ЭТОТ водоём является северной границей Турции.', 'Легко', 'Чёрное море', 'Чёрное море|чёрное море|Черное море|черное море');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (66, 300, 'Именно ТАК в народе называют болезни, связанные с отёчностью.', 'Средне', 'Водянка', 'Водянка|водянка');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (66, 400, 'Именно ЭТА вода в сказках заживляет раны.', 'Сложно', 'Мёртвая', 'Мёртвая|мёртвая|Мертвая|мертвая');
        
        INSERT OR IGNORE INTO questions (category_id, cost, text, difficulty, correct_answer, alternatives) 
        VALUES (66, 500, 'Именно ТАКОЙ воды желают спортсменам-гребцам.', 'Сложно', 'Лёгкой', 'Лёгкой|лёгкой|Легкой|легкой|Лёгкая|лёгкая|Легкая|легкая');
    )";
}