# MySQL
Tutorial from [MySQLTutoria](mysqltutorial.org)

## ER-Diagram of Sample Database
<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/mysql-sample-database.png">

## SELECT

```sql
SELECT select_list
FROM table_name;
```

Every `SELECT` statement returns a table.

`SELECT` can also be used on it's own (without) a `FROM` clause:
```sql
SELECT select_list
```

or used as a simple calculation:
```sql
SELECT 1 + 1;
```
which returns a table with a single column and a single row containing the value `2`:
| 1+1 |
| --- |
| 2   |

or used with built-in functions like NOW() or CONCAT():
```sql
SELECT NOW(), CONCAT('Hello', 'World');
```
which returns a table with two columns and a single row containing the current date and time and the string `HelloWorld`:
| NOW()               | CONCAT('Hello', 'World') |
| ------------------- | ------------------------ |
| 2021-10-13 12:00:00 | HelloWorld               |

For better readability, you can use the `AS` keyword to assign an alias to a column:
```sql
SELECT NOW() AS ts, CONCAT('Hello', 'World') AS greeting;
```
which returns:
| ts                  | greeting   |
| ------------------- | ---------- |
| 2021-10-13 12:00:00 | HelloWorld |

The `AS` keyword is optional.

### Execution order:
The order in which the statements are written does not matter for the execution.  
It is always executed in the following order:

<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/MySQL-SELECT-FROM.svg">

## ORDER BY

```sql
SELECT 
   select_list
FROM 
   table_name
ORDER BY 
   column1 [ASC|DESC], 
   column2 [ASC|DESC],
   ...;
```

`ASC` stands for ascending and is the default order.  
`DESC` stands for descending.

When sorting by multiple columns, the first column is sorted first, then the second column, etc. The second column is only used if the values of the first column are equal.

`ORDER BY` can also be used in combination with expressions, e.g.:
```sql
SELECT 
    orderNumber,
    orderLineNumber,
    quantityOrdered * priceEach
FROM
    orderdetails
ORDER BY subtotal DESC;
```

This returns the following table:
| orderNumber | orderLineNumber | quantityOrdered * priceEach |
| ----------- | --------------- | --------------------------- |
| 10403       | 9               | 11503.14                    |
| 10405       | 5               | 11170.52                    |
| 10407       | 2               | 10723.60                    |
| 10404       | 3               | 10460.16                    |
| 10312       | 3               | 10286.40                    |
| 10424       | 6               | 10072.00                    |
| 10348       | 8               | 9974.40                     |
| 10405       | 3               | 9712.04                     |
| 10196       | 5               | 9571.08                     |
| 10206       | 6               | 9568.73                     |
 ...

The value `NULL` comes before all non-`NULL` values.  
-> is first when sorting in ascending order  
-> is last when sorting in descending order

### Execution Order
`ORDER BY` is always executed after `SELECT` and therefore can only use columns that are available in the result set.

<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/MySQL-ORDER-BY.svg">

## WHERE

The `WHERE` clause filters the rows of a table before they are passed on to a `SELECT` statement.

```sql
SELECT 
    select_list
FROM
    table_name
WHERE
    search_condition;
```

The `WHERE` clause can contain multiple conditions that are connected by logical operators like `AND`, `OR` and `NOT`.

```sql
SELECT 
    lastname, 
    firstname, 
    jobtitle,
    officeCode
FROM
    employees
WHERE
    jobtitle = 'Sales Rep' AND 
    officeCode = 1;
```
Resulting in:
| lastname | firstname | jobtitle  | officeCode |
| -------- | --------- | --------- | ---------- |
| Jennings | Leslie    | Sales Rep | 1          |
| Thompson | Leslie    | Sales Rep | 1          |

Strings can be compared using `=` and `LIKE`.  
`=` is used for exact matches.  
`LIKE` is used for partial and pattern matches.
```sql
SELECT 
    firstName, 
    lastName
FROM
    employees
WHERE
    lastName LIKE '%son'
ORDER BY lastName;
```

The `IN` operator is used to check if a value is in a list of values:
```sql
SELECT 
    firstName, 
    lastName, 
    officeCode
FROM
    employees
WHERE
    officeCode IN (1 , 2, 3)
ORDER BY 
    officeCode;
```

### Execution Order
The `WHERE` clause is executed before the `SELECT` clause.

<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/MySQL-WHERE.svg">

## Joins

Joins are used to combine data from multiple tables.

### INNER JOIN

The `INNER JOIN` returns rows from both tables that satisfy the join condition.

It can be illustrated as follows:
<img src="https://www.mysqltutorial.org/wp-content/uploads/2019/08/mysql-join-inner-join.png">

```sql
SELECT column_list
FROM table_1
INNER JOIN table_2 ON join_condition;
```

Example:
```sql
SELECT 
    m.member_id, 
    m.name AS member, 
    c.committee_id, 
    c.name AS committee
FROM
    members m
INNER JOIN committees c ON c.name = m.name;
```
Resulting in:
| member_id | member | committee_id | committee |
| --------- | ------ | ------------ | --------- |
| 1         | John   | 1            | John      |
| 3         | Mary   | 2            | Mary      |
| 5         | Amelia | 3            | Amelia    |

### LEFT JOIN

The `LEFT JOIN` returns all rows from the left table and the matching rows from the right table. If there is no matching row in the right table, `NULL` values are used.

It can be illustrated as follows:

<img src="https://www.mysqltutorial.org/wp-content/uploads/2019/08/mysql-join-left-join.png">

```sql
SELECT column_list 
FROM table_1 
LEFT JOIN table_2 ON join_condition;
```

Example:
```sql
SELECT 
    m.member_id, 
    m.name AS member, 
    c.committee_id, 
    c.name AS committee
FROM
    members m
LEFT JOIN committees c USING(name);
```
Resulting in:
| member_id | member | committee_id | committee |
| --------- | ------ | ------------ | --------- |
| 1         | John   | 1            | John      |
| 2         | Jane   | NULL         | NULL      |
| 3         | Mary   | 2            | Mary      |
| 4         | David  | NULL         | NULL      |
| 5         | Amelia | 3            | Amelia    |

### RIGHT JOIN

The `RIGHT JOIN` returns all rows from the right table and the matching rows from the left table. If there is no matching row in the left table, `NULL` values are used.

It can be illustrated as follows:

<img src="https://www.mysqltutorial.org/wp-content/uploads/2019/08/mysql-join-right-join.png">

```sql
SELECT column_list
FROM table_1
RIGHT JOIN table_2 ON join_condition;
```

Example:
```sql
SELECT 
    m.member_id, 
    m.name AS member, 
    c.committee_id, 
    c.name AS committee
FROM
    members m
RIGHT JOIN committees c ON c.name = m.name;
```
Resulting in:
| member_id | member | committee_id | committee |
| --------- | ------ | ------------ | --------- |
| 1         | John   | 1            | John      |
| 3         | Mary   | 2            | Mary      |
| 5         | Amelia | 3            | Amelia    |
| NULL      | NULL   | 4            | Joe       |

### CROSS JOIN

The `CROSS JOIN` returns the Cartesian product of the sets of rows from the joined tables. That means, combining each row from the first table with every row from the right table.

```sql
SELECT select_list
FROM table_1
CROSS JOIN table_2;
```
Can also be writte as:
```sql
SELECT select_list
FROM table_1, table_2;
```

Example:
```sql
SELECT 
    m.member_id, 
    m.name AS member, 
    c.committee_id, 
    c.name AS committee
FROM
    members m
CROSS JOIN committees c; 
```
Resulting in:
| member_id | member | committee_id | committee |
| --------- | ------ | ------------ | --------- |
| 1         | John   | 1            | John      |
| 1         | John   | 2            | Mary      |
| 1         | John   | 3            | Amelia    |
| 1         | John   | 4            | Joe       |
| 2         | Jane   | 1            | John      |
| 2         | Jane   | 2            | Mary      |
| 2         | Jane   | 3            | Amelia    |
| 2         | Jane   | 4            | Joe       |
| 3         | Mary   | 1            | John      |
| 3         | Mary   | 2            | Mary      |
| 3         | Mary   | 3            | Amelia    |
| 3         | Mary   | 4            | Joe       |
| 4         | David  | 1            | John      |
| 4         | David  | 2            | Mary      |
| 4         | David  | 3            | Amelia    |
| 4         | David  | 4            | Joe       |
| 5         | Amelia | 1            | John      |
| 5         | Amelia | 2            | Mary      |
| 5         | Amelia | 3            | Amelia    |
| 5         | Amelia | 4            | Joe       |

## GROUP BY

The `GROUP BY` clause groups rows that have the same values into summary rows. It is often used with aggregate functions like `COUNT()`, `MAX()`, `MIN()`, `SUM()` and `AVG()`.

```sql
SELECT 
    column_1,
    aggregate_function(column_2)
FROM
    table_name
WHERE
    condition
GROUP BY column_1;
```

Example:
```sql
SELECT 
  status, 
  COUNT(*) 
FROM 
  orders 
GROUP BY 
  status;
```
Resulting in:
| status     | COUNT(*) |
| ---------- | -------- |
| Shipped    | 303      |
| Resolved   | 4        |
| Cancelled  | 6        |
| On Hold    | 4        |
| Disputed   | 3        |
| In Process | 6        |

Example:
```sql
SELECT 
  status, 
  SUM(quantityOrdered * priceEach) AS amount 
FROM 
  orders 
  INNER JOIN orderdetails USING (orderNumber) 
GROUP BY 
  status;
```
Resulting in:
| status     | amount     |
| ---------- | ---------- |
| Shipped    | 8865094.64 |
| Resolved   | 134235.88  |
| Cancelled  | 238854.18  |
| On Hold    | 169575.61  |
| Disputed   | 61158.78   |
| In Process | 135271.52  |

### Execution Order
<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/MySQL-GROUP-BY.svg">

## HAVING

The `HAVING` clause is used to filter groups.  
It is similar to the `WHERE` clause, but it is used to filter groups created by the `GROUP BY` clause instead of individual rows.

```sql
SELECT 
    select_list
FROM 
    table_name
WHERE 
    search_condition
GROUP BY 
    group_by_expression
HAVING 
    group_condition;
```

Example:
```sql
SELECT 
  ordernumber, 
  SUM(quantityOrdered) AS itemsCount, 
  SUM(priceeach * quantityOrdered) AS total 
FROM 
  orderdetails 
GROUP BY 
  ordernumber 
HAVING 
  total > 1000;
```
Resulting in:
| ordernumber | itemsCount | total    |
| ----------- | ---------- | -------- |
| 10100       | 151        | 10223.83 |
| 10101       | 142        | 10549.01 |
| 10102       | 80         | 5494.78  |

### Execution Order
<img src="https://www.mysqltutorial.org/wp-content/uploads/2023/10/MySQL-HAVING.svg">

## Stored Procedures

A stored procedure is a prepared SQL code that you can save, so the code can be reused over and over again.

```sql
DELIMITER $$

CREATE PROCEDURE GetCustomers()
BEGIN
	SELECT 
		customerName, 
		city, 
		state, 
		postalCode, 
		country
	FROM
		customers
	ORDER BY customerName;    
END$$
DELIMITER ;
```

To execute a stored procedure, use the `CALL` statement:
```sql
CALL GetCustomers();
```

### Advantages of Stored Procedures
- **Network traffic**: Because the commands of a stored procedure are executed as a single batch of code, the amount of network traffic is reduced.
- **Centralized logic**: Because stored procedures are stored in a centralized location, they are easier to maintain and manage.

### Disadvantages of Stored Procedures
- **Resource management**: Because the stored procedure is stored in the database, it uses database resources. Therefore, you need to make sure that the database has enough resources to handle the execution of the stored procedure.
- **Debugging**: Stored procedures are hard to debug.

### Delimiter
The `DELIMITER` statement changes the standard delimiter which is `;`.

```sql
SELECT * FROM products;

DELIMITER //
SELECT * FROM customers//
```

### Stored Procedure Parameters
There are three types of parameters:
- **IN**: The parameter can be used to pass values to the stored procedure.
- **OUT**: The parameter can be used to get values from the stored procedure.
- **INOUT**: The parameter can be used to pass values to and get values from the stored procedure.

```sql
DELIMITER //

CREATE PROCEDURE GetOfficeByCountry(
	IN countryName VARCHAR(255)
)
BEGIN
	SELECT * 
 	FROM offices
	WHERE country = countryName;
END //

DELIMITER ;
```

To execute the stored procedure, use the `CALL` statement:
```sql
CALL GetOfficeByCountry('USA');
```

If you don't pass an argument, you'll get an error.
```sql
Error Code: 1318. Incorrect number of arguments for PROCEDURE classicmodels.GetOfficeByCountry; expected 1, got 0
```

To get the result of an `OUT` parameter, pass a user-defined variable to the `CALL` statement:
```sql
DELIMITER $$

CREATE PROCEDURE GetOrderCountByStatus (
	IN  orderStatus VARCHAR(25),
	OUT total INT
)
BEGIN
	SELECT COUNT(orderNumber)
	INTO total
	FROM orders
	WHERE status = orderStatus;
END$$

DELIMITER ;
```

```sql
CALL GetOrderCountByStatus('Shipped', @total);
```
@total is a user-defined variable that can be accessed with the `SELECT` statement:
```sql
SELECT @total;
``` 

The `INOUT` parameter is used to pass values to and get values from the stored procedure. It is a combination of `IN` and `OUT` parameters.

```sql
DELIMITER $$

CREATE PROCEDURE SetCounter(
	INOUT counter INT,
    IN inc INT
)
BEGIN
	SET counter = counter + inc;
END$$

DELIMITER ;
```

```sql
SET @counter = 1;
CALL SetCounter(@counter, 1); -- 2
CALL SetCounter(@counter, 1); -- 3
CALL SetCounter(@counter, 5); -- 8
SELECT @counter; -- 8
```

### Drop Procedure
```sql
DROP PROCEDURE [IF EXISTS] sp_name;
```
Drops the stored procedure [if it exists].

### Variables
Variables are used to store data, like numbers, text or dates. They are created with the `DECLARE` statement.
```sql
DECLARE variable_name datatype(size) [DEFAULT default_value];
```
For example:
```sql
DECLARE totalSale DEC(10,2) DEFAULT 0.0;
DECLARE totalQty, stockCount INT DEFAULT 0;
DECLARE currency CHAR(3);
```

The can be assigned values with the `SET` statement:
```sql
SET variable_name = value;
```

For example:
```sql
SET totalSale = 1000.00;
SET totalQty = 100;
SET stockCount = 50;
SET currency = 'USD';
```

#### Variable Scope
Variables created within a stored procedure or within a `BEGIN...END` block, go out of scope when the respective block ends.

### List procedures
```sql
SHOW PROCEDURE STATUS [LIKE 'pattern' | WHERE search_condition]
```
or using the routine schema:
```sql
SELECT routine_name
FROM information_schema.routines
WHERE routine_type = 'PROCEDURE'
```

### Conditional Statements
#### IF
```sql
IF condition THEN 
   statements;
END IF;
```
or with an `ELSE` clause:
```sql
IF condition THEN 
   statements;
ELSE
   statements;
END IF;
```
or with an `ELSEIF` clause:
```sql
IF condition THEN 
   statements;
ELSEIF condition THEN
    statements;
ELSE
    statements;
END IF;
```

#### CASE
```sql
CASE case_value
   WHEN when_value1 THEN statements
   WHEN when_value2 THEN statements
   ...
   [ELSE else-statements]
END CASE;
```
When the `ELSE` clause does not exist and the `CASE` cannot find any `when_value` equal to the `case_value`, it issues an error.  
To avoid the error when the `case_value` does not equal any `when_value`, you can use an empty `BEGIN...END` block in the ELSE clause, as follows:
```sql
CASE case_value
    WHEN when_value1 THEN ...
    WHEN when_value2 THEN ...
    ELSE 
        BEGIN
        END;
END CASE;
```

### Loops
#### Basic Loop
```sql
[label]: LOOP
    ...
    -- terminate the loop
    IF condition THEN
        LEAVE [label];
    END IF;
    ...
END LOOP [label];
```
The loop is executed until the `LEAVE` statement is executed.

Additionally, you can use the `ITERATE` statement to skip the current iteration and start a new one:

#### WHILE Loop
```sql
[begin_label:] WHILE search_condition DO
    statement_list
END WHILE [end_label]
```

<img src="https://www.mysqltutorial.org/wp-content/uploads/2019/09/MySQL-WHILE-Loop.png">

```sql
DELIMITER $$

CREATE PROCEDURE loadDates(
    startDate DATE, 
    day INT
)
BEGIN
    
    DECLARE counter INT DEFAULT 0;
    DECLARE currentDate DATE DEFAULT startDate;

    WHILE counter <= day DO
        CALL InsertCalendar(currentDate);
        SET counter = counter + 1;
        SET currentDate = DATE_ADD(currentDate ,INTERVAL 1 day);
    END WHILE;

END$$

DELIMITER ;
```

#### REPEAT Loop
```sql
[begin_label:] REPEAT
    statement_list
UNTIL search_condition
END REPEAT [end_label]
```

<img src="https://www.mysqltutorial.org/wp-content/uploads/2019/09/MySQL-REPEAT-Loop.png">

```sql
DELIMITER $$

CREATE PROCEDURE RepeatDemo()
BEGIN
    DECLARE counter INT DEFAULT 1;
    DECLARE result VARCHAR(100) DEFAULT '';
    
    REPEAT
        SET result = CONCAT(result,counter,',');
        SET counter = counter + 1;
    UNTIL counter >= 10
    END REPEAT;
    
    -- display result
    SELECT result;
END$$

DELIMITER ;
```

### SHOW WARNINGS
```sql
SHOW WARNINGS;
```

For example, when trying to delete a table that does not exist:
```sql
DROP TABLE IF EXISTS abc;
```
A warning is issued:
```sql
Query OK, 0 rows affected, 1 warning (0.01 sec)
```

`SHOW WARNINGS;` would now return a table that looks like this:
| Level | Code | Message                           |
| ----- | ---- | --------------------------------- |
| Note  | 1051 | Unknown table 'classicmodels.abc' |

`SHOW WARNINGS` can also be used with the `COUNT` function:
```sql
SHOW COUNT(*) WARNINGS;
```

### SHOW ERRORS
Works the same way as `SHOW WARNINGS`, but only shows errors.

### DECLARE ... HANDLER

```sql
DECLARE { EXIT | CONTINUE } HANDLER
    FOR condition_value [, condition_value] ...
    statement
```

The `EXIT` and `CONTINUE` specify the action to be taken when the condition is met.
- `EXIT` will terminate the stored procedure.
- `CONTINUE` will continue executing the stored procedure.

`FOR condition_value` specifies the condition that triggers the handler.
Must be a `mysql_error_code` or an `SQLSTATE` value.

`statement` is the statement that is executed when the condition is met.

Example:
```sql
DELIMITER //

CREATE PROCEDURE insert_user(
	IN p_username VARCHAR(50), 
    IN p_email VARCHAR(50)
)
BEGIN
  -- SQLSTATE for unique constraint violation
  DECLARE EXIT HANDLER FOR SQLSTATE '23000'
  BEGIN
    -- Handler actions when a duplicate username is detected
    SELECT 'Error: Duplicate username. Please choose a different username.' AS Message;
  END;

  -- Attempt to insert the user into the table
  INSERT INTO users (username, email) VALUES (p_username, p_email);

  -- If the insertion was successful, display a success message
  SELECT 'User inserted successfully' AS Message;

END //

DELIMITER ;
```

### Cursor

```sql
-- declare a cursor
DECLARE cursor_name CURSOR FOR 
SELECT column1, column2 
FROM your_table 
WHERE your_condition;

-- open the cursor
OPEN cursor_name;

FETCH cursor_name INTO variable1, variable2;
-- process the data


-- close the cursor
CLOSE cursor_name;
```

A cursor are used to process individual rows returned by a query. A cursor is similar to an iterator or pointer that points to a row in a result set.

- `DECLARE` statement declares a cursor.
- `OPEN` statement opens a cursor.
- `FETCH` statement retrieves the next row from the cursor and assigns the column values to the specified variables.
- `CLOSE` statement closes a cursor.

<img src="https://www.mysqltutorial.org/wp-content/uploads/2009/12/mysql-cursor.png">

Example:
```sql
DELIMITER $$

CREATE PROCEDURE create_email_list (
	INOUT email_list TEXT
)
BEGIN
	DECLARE done BOOL DEFAULT false;
	DECLARE email_address VARCHAR(100) DEFAULT "";
    
	-- declare cursor for employee email
	DECLARE cur CURSOR FOR SELECT email FROM employees;

	-- declare NOT FOUND handler
	DECLARE CONTINUE HANDLER 
        FOR NOT FOUND SET done = true;
	
    -- open the cursor
	OPEN cur;
	
    SET email_list = '';
	
    process_email: LOOP
		
        FETCH cur INTO email_address;
        
		IF done = true THEN 
			LEAVE process_email;
		END IF;
		
        -- concatenate the email into the emailList
		SET email_list = CONCAT(email_address,";",email_list);
	END LOOP;
    
    -- close the cursor
	CLOSE cur;

END$$

DELIMITER ;
```

## Triggers

A trigger is a stored program that is executed automatically to respond to a specific event e.g. insert, update or delete.

```sql
CREATE TRIGGER trigger_name
{BEFORE | AFTER} {INSERT | UPDATE | DELETE}
ON table_name
FOR EACH ROW
BEGIN
    -- Trigger body (SQL statements)
END;
```

To distinguish between the value of the columns `BEFORE` and `AFTER` the event has fired, you use the `NEW` and `OLD` modifiers.

```sql
DELIMITER //

CREATE TRIGGER update_items_trigger
AFTER UPDATE
ON items
FOR EACH ROW
BEGIN
    INSERT INTO item_changes (item_id, change_type)
    VALUES (NEW.id, 'UPDATE');
END;
//

DELIMITER ;
```

## Views

Views are virtual tables that are created by a query. They are not physically stored in the database.

```sql
CREATE VIEW customerPayments
AS 
SELECT
    customerName, 
    checkNumber, 
    paymentDate, 
    amount
FROM
    customers
INNER JOIN
    payments USING (customerNumber);
```

After a view is created it can be queried like any other table:
```sql
SELECT * FROM customerPayments;
```
When the view is used, the saved query is executed and the result is used as the source table.  
Inserting or other write operations are not possible.
