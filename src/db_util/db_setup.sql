DO
$body$
BEGIN
   IF NOT EXISTS (
       SELECT * FROM pg_catalog.pg_user WHERE usename = 'gob_user')
   THEN
      CREATE ROLE gob_user LOGIN PASSWORD 'psqlisstupid';
   END IF;
END
$body$;

CREATE TABLE IF NOT EXISTS sentences (
    id                SERIAL PRIMARY KEY,
    original          VARCHAR NOT NULL,
    hiragana          VARCHAR NOT NULL,
    translation       VARCHAR NOT NULL,
    context           VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE sentences TO gob_user;

CREATE TABLE IF NOT EXISTS kanji (
    kanji             VARCHAR PRIMARY KEY,
    kunyomi           VARCHAR,
    onyomi            VARCHAR,
    translation       VARCHAR NOT NULL,
    notes             VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE kanji TO gob_user;

CREATE TABLE IF NOT EXISTS jukugo (
    kanji             VARCHAR PRIMARY KEY,
    hiragana          VARCHAR NOT NULL,
    translation       VARCHAR NOT NULL,
    notes             VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE jukugo TO gob_user;

GRANT ALL PRIVILEGES ON DATABASE gobware TO gob_user;
