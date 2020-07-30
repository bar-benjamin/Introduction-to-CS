-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred
SELECT title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = "Johnny Depp"
INTERSECT
SELECT title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = "Helena Bonham Carter";