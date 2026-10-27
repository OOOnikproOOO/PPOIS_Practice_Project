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
    )";
}