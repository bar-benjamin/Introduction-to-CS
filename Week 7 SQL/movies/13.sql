-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT(people.name) from people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE (movies.id IN 
(SELECT movies.id from movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon" AND birth = 1958))
AND people.name != "Kevin Bacon";