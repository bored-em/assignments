
-- (1)List all swimmer names and their primary caretaker names in the following format.

SELECT DISTINCT CONCAT(s.fname, ' ', s.lname) AS swimmer, 
	CONCAT(c.fname, ' ', c.lname) AS 'Primary Caretaker'
FROM swimmer AS s 
	INNER JOIN caretaker AS c ON(s.Main_CT_Id = c.CT_Id);

-- (2)List the names of the swimmers with current level (i.e. currentLevelId) is Yellow 
-- or above. Note that the level of Yellow has a LevelId of 3. However, you should not 
-- use 3 in your query. You should use "Yellow".

SELECT DISTINCT s.lname, s.fname, s.currentLevelId
FROM swimmer AS s 
	INNER JOIN level AS l ON(s.CurrentLevelId = LevelId)
WHERE l.Level != 'Green' 
	AND l.Level != 'Blue';

-- (3)List the swimmer names (in a single column) that have participated in an event 
-- of a meet in a venue with a phone with an area code of 713 in the following format. 

SELECT DISTINCT CONCAT(s.fname, ' ', s.lname) AS 'Swimmer', m.title AS 'Meet', 
	v.Name AS 'Venue', v.phone
FROM swimmer AS s 
	INNER JOIN participation AS p ON(s.SwimmerId = p.SwimmerId) 
	INNER JOIN event AS e ON(p.EventId = e.EventId)
	INNER JOIN meet AS m ON(e.MeetId = m.MeetId) 
	INNER JOIN venue AS v ON(m.VenueId = v.VenueId)
WHERE v.Phone like '%713%';

-- (4)List all swimmers (their names, levels AND event titles) who have participated 
-- in events in the meet 'UHCL Open' in the following manners.

SELECT DISTINCT CONCAT(s.fname, '', s.lname) AS 'Swimmer in UHCL Open', l.Level, e.Title
FROM swimmer AS s 
	INNER JOIN participation AS p ON(s.SwimmerId = p.SwimmerId)
	INNER JOIN event AS e ON(p.EventId = e.EventId)
	INNER JOIN level AS l ON(e.LevelId = l.LevelId)
	INNER JOIN meet AS m ON(e.MeetId = m.MeetId)
WHERE m.Title = 'UHCL Open';

-- (5)List all swimmers with their primary caretakers and their other caretakers in the 
-- following manner. Order the result by last names and then first names of the swimmers.

SELECT DISTINCT CONCAT(s.fname, ' ', s.LName)  AS 'Swimmer',
	CONCAT(c.FName, ' ' , c.LName) AS 'Primary Caretaker',
	GROUP_CONCAT(DISTINCT CONCAT(oc.FName, ' ', oc.LName) 
	ORDER BY oc.LName, oc.FName SEPARATOR '; ') AS 'Other Caretakers'
FROM swimmer AS s 
	INNER JOIN caretaker AS c ON(s.Main_CT_Id = c.CT_Id) 
	LEFT JOIN othercaretaker AS o ON(s.SwimmerId = o.SwimmerId)
	LEFT JOIN caretaker AS oc ON(o.CT_Id = oc.CT_Id)
GROUP BY s.SwimmerId, c.FName, c.LName
ORDER BY s.lname, s.fname;

-- (6)List the swimmers (names and their number of participated events) who have 
-- participated in two or more events in 'UHCL Open' in the following format.

SELECT DISTINCT CONCAT(s.fname, ' ', s.lname) AS 'Swimmer', 
	COUNT(p.EventId) AS 'Number of Events in UHCL Open'
FROM swimmer AS s 
	INNER JOIN participation AS p ON(s.SwimmerId = p.SwimmerId)
	INNER JOIN event AS e ON(p.EventId = e.EventId)
	INNER JOIN meet AS m ON(e.MeetId = m.MeetId)
WHERE m.Title = 'UHCL Open'
GROUP BY s.SwimmerId, s.FName, s.lname
HAVING COUNT(p.EventId) >= 2
ORDER BY s.fname;


-- (7)List the name of the swimmers who have participated in in event 3 but not event 4.

SELECT DISTINCT CONCAT(s.fname, ' ', s.lname) AS 'swimmer'
FROM swimmer AS s 
	INNER JOIN participation AS p ON(s.SwimmerId = p.SwimmerId)
WHERE p.EventId = 3 AND s.SwimmerId 
	NOT IN(SELECT SwimmerID 
			FROM participation 
			WHERE EventId = 4);

-- (8)List the titles of the events with the least number of participants in the following format.

SELECT DISTINCT CONCAT(m.Title, ': ', e.Title) AS 'Least popular event', 
	COUNT(p.SwimmerId) AS 'number of swimmers'
FROM meet AS m
	INNER JOIN event AS e ON(m.MeetId = e.MeetId) 
	LEFT JOIN participation AS p ON(p.EventId = e.EventId)
GROUP BY e.EventId, m.Title, e.Title
HAVING COUNT(p.SwimmerId) = (SELECT MIN(c) 
	FROM (SELECT COUNT(SwimmerId) AS c 
			FROM participation
			GROUP BY EventId) AS cs);
	
	
	