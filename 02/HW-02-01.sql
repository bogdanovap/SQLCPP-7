-- создаем таблицы с данными - справочниками
drop table if exists jenres;
create table jenres(
    id serial primary key,
    jenre_name varchar(100) not null
);

drop table if exists artist;
create table artist(
    id serial primary key,
    name varchar(100) not null
);

drop table if exists album;
create table album(
    id serial primary key,
    name varchar(100) not null,
    year integer not null
);

drop table if exists track;
create table track(
    id serial primary key,
    name varchar(100) not null,
    duration integer not null,
    album_id integer not null references album(id)
);

drop table if exists collections;
create table collections(
    id serial primary key,
    name varchar(100) not null,
    year integer not null
);

-- создаем таблицы - связи
drop table if exists artist_jenre;
create table artist_jenre(
    id serial primary key,
    artist_id integer not null references artist(id),
    jenre_id integer not null references jenres(id)
);

drop table if exists artist_album;
create table artist_album(
    id serial primary key,
    artist_id integer not null references artist(id),
    album_id integer not null references album(id)
);

drop table if exists collections_track;
create table collections_track(
    id serial primary key,
    collections_id integer not null references collections(id),
    track_id integer not null references track(id)
);
