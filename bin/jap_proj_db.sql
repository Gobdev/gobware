-- CREATE TABLES

DROP TABLE IF EXISTS words;
DROP TABLE IF EXISTS phrases;

CREATE TABLE words (
    character       VARCHAR(10) PRIMARY KEY,
    onyomi          VARCHAR(50),
    kunyomi         VARCHAR(50),
    translation     VARCHAR(100)
);

CREATE TABLE phrases (
    phrase          VARCHAR(200) PRIMARY KEY,
    phonetic        VARCHAR(200),
    translation     VARCHAR(200)
);

INSERT INTO words (character, onyomi, kunyomi, translation) VALUES
    ('小', 'しょう', 'ちい; こ; お', 'small'),
    ('月', 'がつ; げつ', 'つき', 'month; moon');

INSERT INTO phrases (phrase, phonetic, translation) VALUES
    ('おはようございます', 'おはようございます', 'Good morning.'),
    ('寿司を食べます', 'すしをたべます', 'I eat sushi.');

GRANT ALL PRIVILEGES ON DATABASE jap_proj TO jap_proj_user;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO jap_proj_user;
