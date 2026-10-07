-- [1] List the stuId, names, and majors of students minoring in ITEC 
-- and having 1016 as their faculty advisors in the following manner.

-- Output: stuid, fname, lname, major
-- Sources: student, department, faculty
-- Conditions: minor in ITEC and 1016 faculty advisor

SELECT DISTINCT s.stuid, 
	CONCAT(s.fname, ' ', s.lname) AS student, 
	d.deptname AS major
FROM student AS s 
	INNER JOIN department AS d ON (s.major = d.deptcode)
	INNER JOIN faculty as f ON (s.major = f.deptcode)
WHERE s.minor = 'ITEC'
	AND f.facId = '1016';

-- [2] List the names, numbers of credits (ach), majors, and advisor names of 
-- students having 1011, 1012 or 1015 as faculty advisor in the following manner.

-- Output: stuid, fname, lname, ach, major, advisor(fname, lname)
-- Soruces: student, department, faculty
-- Conditions: 1011, 1012, or 1015 advisor

SELECT DISTINCT s.stuid, 
	CONCAT(s.fname, ' ', s.lname) AS student, 
	s.ach AS credits,
	d.deptname AS major, 
	CONCAT(f.fname, ' ', f.lname) AS advisor
FROM student AS s 
	INNER JOIN department AS d ON (s.major = d.deptcode)
	INNER JOIN faculty as f ON (s.advisor = f.facId)
WHERE f.facId IN ('1011', '1012', '1015');

-- [3] List the enrollment information of all CSCI courses that have been offered in the following manner.

-- Output: courseid(rubric, number), course, credits, semester, year, instructor(fname,lname), fname, lname, grade
-- Sources: student, course, class, faculty, enroll
-- Conditions: all CSCI courses

SELECT DISTINCT 
	CONCAT(co.rubric, ' ', co.number) AS "course id", 
	co.title AS course, 
	co.credits, 
	c.semester, 
	c.year, 
	CONCAT(f.fname, ' ', f.lname) AS instructor, 
	CONCAT(s.fname, ' ' , s.lname) as student,
	e.grade
FROM course AS co 
	INNER JOIN class AS c ON (co.courseId = c.courseId)
	INNER JOIN faculty AS f ON (f.facId = c.facId)
	INNER JOIN enroll AS e ON (e.classId = c.classId)
	INNER JOIN student AS s ON (s.stuId = e.stuId)
WHERE co.rubric = 'CSCI';

-- [4] Repeat [3], show only those entries with a grade of B or above.

-- Output:courseid(rubric, number), course, credits, semester, year, instructor(fname,lname), fname, lname, grade
-- Sources: student, course, class, faculty, enroll
-- Conditions: all CSCI courses and only with B and above.

SELECT DISTINCT 
	CONCAT(co.rubric, ' ', co.number) AS "course id", 
	co.title AS course, 
	co.credits, 
	c.semester, 
	c.year, 
	CONCAT(f.fname, ' ', f.lname) AS instructor, 
	CONCAT(s.fname, ' ' , s.lname) as student,
	e.grade
FROM course AS co 
	INNER JOIN class AS c ON (co.courseId = c.courseId)
	INNER JOIN faculty AS f ON (f.facId = c.facId)
	INNER JOIN enroll AS e ON (e.classId = c.classId)
	INNER JOIN student AS s ON (s.stuId = e.stuId)
WHERE co.rubric = 'CSCI' 
	AND e.grade IN ('B', 'B+', 'A-', 'A');

-- [5] List the names and ids of all students who have a failing grade (C- or below) or 
-- no grade in some courses in the following manner.

-- Output:fname, lname, stuid
-- Sources: student, grade
-- Conditions: only students with failing grade or no grade

SELECT DISTINCT 
	CONCAT(s.fname, ' ', s.lname) AS 'student with failing grades or no grade', s.stuId AS 'student id'
FROM student AS s
	INNER JOIN enroll AS e ON (e.stuId = s.stuId)
WHERE e.grade IN ('C-', 'D', 'F') 
	OR e.grade IS NULL;