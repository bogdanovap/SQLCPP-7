-- Количество исполнителей в каждом жанре
select jenre_id, count(artist_id) as nb_artists
from artist_jenre
group by jenre_id;

-- Количество треков, вошедших в альбомы 2019-2020 годов
select count(track.id) as nb_tracks
from track
join album on track.album_id = album.id
where album.year between 2019 and 2020;

-- Средняя продолжительность треков по каждому альбому
select album.name, avg(duration) as avg_duration
from track
join album on track.album_id = album.id
group by album.name;

-- Все исполнители, которые не выпустили альбомы в 2020 году
select distinct artist.name
from artist
join artist_album on artist.id = artist_album.artist_id
join album on artist_album.album_id = album.id
where album.year != 2020;

-- Названия сборников, в которых присутствует конкретный исполнитель 'Queen'
select collections.name
from collections
join collections_track on collections.id = collections_track.collections_id
join track on collections_track.track_id = track.id
join album on track.album_id = album.id
join artist_album on album.id = artist_album.album_id
join artist on artist_album.artist_id = artist.id
where artist.name = 'queen';
