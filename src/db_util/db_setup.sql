DO
$body$
BEGIN
   IF NOT EXISTS (
       SELECT * FROM pg_catalog.pg_user WHERE usename = 'jap_proj_user')
   THEN
      CREATE ROLE jap_proj_user LOGIN PASSWORD 'psqlisstupid';
   END IF;
END
$body$;

CREATE TABLE IF NOT EXISTS sentences (
    id                SERIAL PRIMARY KEY,
    originial         VARCHAR NOT NULL,
    hiragana          VARCHAR NOT NULL,
    translation       VARCHAR NOT NULL,
    context           VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE sentences TO jap_proj_user;

CREATE TABLE IF NOT EXISTS kanji (
    kanji             VARCHAR PRIMARY KEY,
    kunyomi           VARCHAR,
    onyomi            VARCHAR,
    translation       VARCHAR NOT NULL,
    notes             VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE kanji TO jap_proj_user;

CREATE TABLE IF NOT EXISTS jukugo (
    kanji             VARCHAR PRIMARY KEY,
    hiragana          VARCHAR NOT NULL,
    translation       VARCHAR NOT NULL,
    notes             VARCHAR
);
GRANT ALL PRIVILEGES ON TABLE jukugo TO jap_proj_user;
