# INSERT INTO

```sql
INSERT INTO table_name (column1,column2,column3,...) VALUES (value1,value2,value3,...);
```

插入数据

可以省略$(column1,column2,column3,...)$，即不指定列名

# UPDATE

```sql
UPDATE table_name
SET column1=value1,column2=value2,...
WHERE some_column=some_value;
```

更新

# SELECT LIMIT

```sql
SELECT column_name(s) 
FROM table_name 
LIMIT number;
```

mysql下使用，选取指定数量的行

# LIKE

```sql
SELECT column_name(s)
FROM table_name
WHERE column_name LIKE pattern;
```

选取指定模式的行。模式用正则表示

栗子：选取name列G开头的行

```
SELECT * FROM Websites
WHERE name LIKE 'G%';
```

# 通配符

```
% 0或多个字符
_ 1个字符
[charlist] 字符列中的任何单一字符
[^charlist]或[!charlist] 不在字符列中的任何单一字符
```

# IN

```SELECT *column_name(s)*
SELECT column_name(s)
FROM table_name
WHERE column_name IN (value1,value2,...);
```

配合where使用，可以选取多个值

# BETWEEN

```
SELECT column_name(s)
FROM table_name
WHERE column_name BETWEEN value1 AND value2;
```

配合WHERE使用，value可以为数字、日期、字符串

## 日期

注意截取时间为当日00:00:00，即

```
BETWEEN '2010-01-01' AND '2012-12-31'
```

是无法选取到2012-12-31当日的

# AS

```
# 列
SELECT column_name AS alias_name
FROM table_name;
# 表
SELECT column_name(s)
FROM table_name AS alias_name;
```

别名

# JOIN

分为LEFT JOIN、RIGHT JOIN、INNER JOIN、OUTER JOIN四种，有7用法

![sql-join](..\picture\sql-join.png)

# UNION

```
SELECT column_name(s) FROM table1
UNION
SELECT column_name(s) FROM table2;
```

合并两个及以上SELECT语句的结果集

若允许存在重复值，使用 UNION ALL

# INSERT INTO SELECT

```sql
INSERT INTO table2
SELECT * FROM table1;
```

从table1中选择行插入到table2中

# CREATE TABLE

```
CREATE TABLE table_name
(
column_name1 data_type(size),
column_name2 data_type(size),
column_name3 data_type(size),
....
);
```

# FOREIGN KEY

```
FOREIGN KEY (P_Id) REFERENCES Persons(P_Id)
```

指向另外一个表中的UNIQUE KEY

# GROUP BY

```
SELECT column_name, aggregate_function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name
```

# HAVING

```
SELECT column_name, aggregate_function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name
HAVING aggregate_function(column_name) operator value
```

## 与WHERE区别

WHERE不能和聚合函数一起使用

WHERE在分组前使用，HAVING在分组后使用

没有聚合函数也可以使用having过滤，但必须在GROUP BY子句后使用

# CASE WHEN THEN

```
case sex
  when '1' then '男'
  when '2' then '女’
  else '其他' end
--case搜索函数
case when sex = '1' then '男'
     when sex = '2' then '女'
     else '其他' end
```

# LIMIT

```mysql
LIMIT [offset,] rows | rows OFFSET offset
# 栗子
select * from table limit 2,1;                 
# 含义是跳过2条取出1条数据，limit后面是从第2条开始读，读取1条信息，即读取第3条数据

select * from table limit 2 offset 1;      
#含义是从第1条（不包括）数据开始取出2条数据，limit后面跟的是2条数据，offset后面是从第1条开始读取，即读取第2,3条
```

要注意LIMIT后，只能接变量或者常量，不能接如（N-1）之类的运算

# IFNULL、ISNULL、NULLIF

## IFNULL(expr1,expr2)

若expr1不为NULL，返回值为expr1；否则返回值为expr2

## ISNULL(expr)

若expr返回值为NULL，则返回值为1；否则返回值为0

# 临时表

```
SELECT 
	(SELECT  * FROM TABLE) AS 列名
```



# 聚合函数

从列中取值，返回一个单一值

```
AVG() 返回平均数
COUNT() 返回行数
FIRST() 返回第一个记录的值
LAST() 返回最后一个记录的值
MAX() 返回最大值
MIN() 返回最小值
SUM() 返回总和
```

# 标量函数

基于输入值，返回单一值

```
UCASE() - 将某个字段转换为大写
LCASE() - 将某个字段转换为小写
MID() - 从某个文本字段提取字符，MySql 中使用
SubString(字段，1，end) - 从某个文本字段提取字符
LEN() - 返回某个文本字段的长度
ROUND() - 对某个数值字段进行指定小数位数的四舍五入
NOW() - 返回当前的系统日期和时间
FORMAT() - 格式化某个字段的显示方式
```

# 自定义函数

```
 CREATE FUNCTION myFunction
(in_string VARCHAR(255),
in_find_str VARCHAR(20),
 in_repl_str VARCHAR(20))

 RETURNS VARCHAR(255)
 BEGIN
 DECLARE l_new_string VARCHAR(255);
 DECLARE l_find_pos INT;

 SET l_find_pos=INSTR(in_string,in_find_str);

 IF (l_find_pos>0) THEN
 SET l_new_string=INSERT(in_string,l_find_pos,LENGTH(in_find_str),in_repl_str);
 ELSE
 SET l_new_string=in_string;
 END IF;
 RETURN(l_new_string);

 END$$
```



# 注意事项

## datediff

用于日期的比较

```
date(datepart,startdate, enddate)
# datepart中为如dd等表示时间的缩写
```

# LEETCODE题库

## 175 组合两个表

考察LEFT JOIN

```
# Write your MySQL query statement below
SELECT Person.FirstName, Person.LastName, Address.City, Address.state
FROM Person LEFT JOIN Address
ON Person.PersonId = Address.PersonId;
```

## 176 第二高的薪水

考察IFNULL、临时表、LIMIT OFFSET

```
SELECT IFNULL(
    (SELECT DISTINCT Salary from Employee
    ORDER BY Salary DESC
    LIMIT 1 OFFSET 1),
    NULL
) AS SecondHighestSalary;
```

## 177 第N高的薪水

考察自定义函数

```
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    SET n = N-1;
  RETURN (
      # Write your MySQL query statement below.

        SELECT DISTINCT Salary FROM Employee
        ORDER BY Salary DESC LIMIT n,1
          #ORDER BY Salary DESC limit (N-1), 1
        
  );
END

```

## 178 分数排名

一个表可以以别名的方式引用两次

注意"Rank"为关键字，要加双引号

```
select s1.Score,count(distinct(s2.score)) Rank
from
Scores s1,Scores s2
where
s1.score<=s2.score
group by s1.Id
order by Rank
```

## 180 连续出现的数字

写法1，注意要distinct

```
# Write your MySQL query statement below
SELECT distinct l1.Num ConsecutiveNums 
FROM Logs l1, Logs l2, Logs l3
WHERE 
    l1.Id + 1 = l2.Id and l1.Num = l2.Num and
    l1.Id + 2 = l3.Id and l1.Num = l3.Num 
```

写法2，考察case when then else end和用户定义变量

用户定义变量：@开头

```
SELECT  DISTINCT(Num) AS ConsecutiveNums
FROM (
    SELECT
    Num,
    @counter := IF(@prev = Num, @counter + 1, 1) AS how_many_cnt_in_a_row, # IF(判断句，执行句1，执行句2)
    @prev := Num #赋值
    FROM Logs y, (SELECT @counter:=1, @prev:=NULL) vars
) sq
WHERE how_many_cnt_in_a_row >= 3
```

## 181 超过经理收入的员工

写法1，考察join

join=inner  join

若此处使用left join，只会返回全部e1的数据

```
select e1.name as Employee
from Employee e1  join Employee e2
on
    e1.ManagerId is not NULL and
    e2.Id = e1.ManagerId and
    e1.Salary > e2.Salary
;
```

写法2，考察where

即使不用join，也可以在from后接多个表

```
select e1.Name as Employee 
from Employee e1, Employee e2
where e1.ManagerId = e2.Id and e1.Salary > e2.Salary
```

## 182 查找重复的电子邮箱

写法1，考察distinct

```
select 
    distinct p1.Email
from 
    Person p1, Person p2
where 
    p1.Id != p2.Id and 
    p1.Email = p2.Email
```

写法2，考察group by having和count

使用sql的聚合函数时，必须使用group by和having语句，不能使用where

```
select Email
from Person
group by Email
having count(Email) > 1;
```



## 183 从不订购的客户

【怎么选取不在B表中的A表中的一些数据】

写法1，考察left join on where

注意on后面跟的是连接A表和B表的条件。要想进行筛选，还需后接where

```
select 
    c1.Name as Customers
from 
    Customers c1 LEFT JOIN (
        select distinct c2.Id, c2.Name
        from Customers c2, Orders o2
        where c2.Id = o2.CustomerId
    ) as c3
on
    c1.Id = c3.Id
where
    c3.Id is NULL 
```

写法2

```
select customers.name as 'Customers'
from customers
where customers.id not in
(
    select customerid from orders
);

```



## 184 部门最高工资的员工

考察聚合函数的条件筛选

使用group by即可

```
select 
    d1.Name as Department, e1.Name as Employee, e1.Salary as Salary
from
    Employee e1, Department d1, (
        select distinct max(e2.Salary) as Salary, e2.DepartmentId as DepartmentId
        from Employee e2
        group by e2.DepartmentId
    ) temp1
where
    e1.DepartmentId = d1.Id and
    d1.Id = temp1.DepartmentId and
    e1.Salary = temp1.Salary
```

## 196 删除重复的电子邮箱

考察delete

```
delete 
    p1
from
    Person p1, Person p2
where
    p1.Email = p2.Email and p1.Id > p2.Id
```

## 197 上升的温度

考察DATEDIFF

```
# Write your MySQL query statement below
select 
    w1.Id
from
    Weather w1, Weather w2
where
    DATEDIFF(w1.RecordDate, w2.RecordDate)=1 and
    w1.Temperature > w2.Temperature
```

