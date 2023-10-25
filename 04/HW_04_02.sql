-- Название и продолжительность самого длительного трека.
select name, duration
from track
order by duration desc
limit 1;

-- Название треков, продолжительность которых не менее 3,5 минут
select name
from track
where duration >= 3.5;

-- Названия сборников, вышедших в период с 2018 по 2020 годы включительно
select name
from collections
where year between 2018 and 2020;

-- Исполнители, чьё имя состоит из одного слова
select name
from artist
where not (name like '% %');

-- Название треков, которые содержат слова «мой» или «my».
select name
from track
where name like '%my%' or name like '%мой%';