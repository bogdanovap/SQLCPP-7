insert into artist (name)
values
        ('the beatles'),('queen'),
        ('prince'),('madonna'),
        ('louis armstrong'),('ella fitzgerald'),
        ('james brown'),('steve wonder');

insert into jenres (jenre_name)
values
    ('rock'), ('pop'), ('jazz'), ('blues'), ('funk');

insert into artist_jenre (artist_id, jenre_id)
values
       (1, 1), (2,1),
       (3, 2), (4,2),
       (5, 3), (6,3),
       (7, 4), (8,4);

insert into album (name, year)
values
    ('abbey road', 1969),('revolver', 1966),
       ('hot space', 1982),('queen', 1973),
       ('prince', 1979),('controversy', 1981),
       ('music', 2020),('mdna', 2012),
       ('porgy and the bess', 1958), ('ella and louis', 1956),
       ('ella and louis again', 1957),('ella in hollywood', 1961),
       ('live at the appollo', 2019), ('gravity', 1986),
       ('innervisions', 1973),('the woman in red', 1984);

insert into artist_album (album_id, artist_id)
values
    (1, 1), (2,1),
       (3, 2), (4,2),
       (5, 3), (6,3),
       (7, 4), (8,4),
       (9, 5), (10,5), (10,6),
       (11, 5), (11, 6), (12,6),
       (13, 7), (14,7),
       (15, 8), (16,8);

insert into track (name, duration, album_id)
VALUES
       ('track 1', 5, 1),
       ('track 2', 8, 2),
       ('track 3', 2, 3),
       ('track 4', 1, 4),
       ('track 5', 5, 16),
       ('track 6', 6, 15),
       ('track 7', 8, 14),
       ('track 8', 9, 2),
       ('track 9', 2, 15),
       ('track 10', 4, 12),
       ('track 11', 5, 11),
       ('track 12', 9, 10),
       ('track 13', 5, 9),
       ('track 14', 3, 8),
       ('track 15', 3, 7);

insert into collections (name, year)
VALUES
       ('sbornik 1', 2007),
       ('sbornik 2', 2009),
       ('sbornik 3', 2010),
       ('sbornik 4', 2012),
       ('sbornik 5', 2014),
       ('sbornik 6', 2015),
       ('sbornik 7', 2020),
       ('sbornik 8', 2022);

insert into collections_track (collections_id, track_id)
values
       (1,2),
       (2,2),
       (2,3),
       (2,4),
       (3,5),
       (4,6),
       (5,8);
