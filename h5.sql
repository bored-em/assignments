
-- [1] Using toyu, show the numbers of majors in departments and colleges in the following manner.
WITH sub AS (SELECT DISTINCT sc.schoolCode AS college,
	CONCAT(d.deptCode, ': ', d.deptName) AS department,
	COUNT(distinct s.stuId) AS num_major
FROM school AS sc 
	LEFT JOIN department AS d ON(sc.schoolCode = d.schoolCode)
	LEFT JOIN student AS s ON s.major = d.deptCode
GROUP BY college, department)
SELECT college,
	SUM(num_major) OVER(PARTITION BY college) AS "# majors in college", 
	department, num_major AS "# majors in department"
FROM sub
ORDER BY college;

-- [2] List the number of FK of tables in toyu that have at least one foreign key.
SELECT inf.TABLE_NAME AS 'table', COUNT(inf.REFERENCED_TABLE_NAME) AS num_fk
FROM information_schema.REFERENTIAL_CONSTRAINTS AS inf
WHERE inf.CONSTRAINT_SCHEMA = 'toyu'
GROUP BY inf.TABLE_NAME;

-- [3] Write a procedure foreign_keys of a table of an INNODB schema. 
DELIMITER $$
DROP PROCEDURE IF EXISTS foreign_keys $$ 

CREATE PROCEDURE foreign_keys(
   IN db_name VARCHAR(64),  
   IN table_name VARCHAR(64),
   OUT n_fk INT)
BEGIN
   SELECT COUNT(DISTINCT refc.CONSTRAINT_NAME) INTO n_fk
   FROM information_schema.REFERENTIAL_CONSTRAINTS AS refc
   WHERE refc.CONSTRAINT_SCHEMA = db_name
   AND refc.TABLE_NAME = table_name;
   SELECT CONCAT(db_name, '.', table_name, ': ', n_fk) AS "table: number of foreign keys";
   IF n_fk > 0 THEN
      SELECT 
         keyu.COLUMN_NAME AS column_name,
      	CONCAT(keyu.REFERENCED_TABLE_NAME, '.', keyu.REFERENCED_COLUMN_NAME) 
			AS "referenced_table.column"
   	FROM information_schema.KEY_COLUMN_USAGE AS keyu
      WHERE keyu.TABLE_SCHEMA = db_name 
      	AND keyu.TABLE_NAME = table_name
      	AND keyu.REFERENCED_TABLE_NAME IS NOT NULL;
   END IF;
END $$
DELIMITER ;

-- [4] Write a function column_count to count the number of columns in a MySQL table.
DELIMITER $$
DROP FUNCTION IF EXISTS column_count $$ 

CREATE FUNCTION column_count(
   db_name VARCHAR(64), 
   table_name VARCHAR(64)) 
	RETURNS INT
DETERMINISTIC
BEGIN
   DECLARE col_count INT;
   SELECT COUNT(*) INTO col_count
   FROM information_schema.COLUMNS as inf
   WHERE inf.TABLE_SCHEMA = db_name 
	AND inf.TABLE_NAME = table_name;
   RETURN col_count;
END $$
DELIMITER ;