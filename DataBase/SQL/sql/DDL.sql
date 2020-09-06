/*

六大约束
NOT NULL 	非空
DEFAULT  	默认
PRIMARY KEY	主键,唯一非空
UNIQUE 		唯一,可以空
CHECK		检查
FOREIGN KEY 外键，限制两个表的关系
			该字段的值来自于主表关联列的值

列级约束:
都支持，外键没有效果
表级约束：
	除了非空和默认
*/
-- CREATE DATABASE IF NOT EXISTS students;
-- 
-- USE students;

-- CREATE TABLE 
-- IF NOT EXISTS 
-- stu_info(
-- 	id 			INT 		PRIMARY KEY,
-- 	`name` 		VARCHAR(20) NOT NULL,
-- 	gender 		CHAR(1) 	CHECK(gender='男' or gender= '女'),
-- 	seat 		INT 		UNIQUE,
-- 	age			INT 		DEFAULT 18,
-- 	major_id 	INT			REFERENCES major(id)
-- );
-- 
-- CREATE TABLE 
-- IF NOT EXISTS 
-- major_info(
-- 	id 			INT 		PRIMARY KEY,
-- 	`name`		VARCHAR(20)	
-- );
-- 
-- DROP TABLE IF EXISTS stu_info;

-- 名字可以不起

-- CREATE TABLE
-- IF NOT EXISTS
-- stu_info(
-- 	id 			INT	auto_increment,	
-- 	`name` 		VARCHAR(20), 
-- 	gender 		CHAR(1), 	
-- 	seat 		INT, 		
-- 	age			INT, 		
-- 	major_id 	INT,
-- 	
-- 	PRIMARY KEY(id),
-- 	UNIQUE(seat),
-- 	CONSTRAINT 	ck	CHECK(gender='男' or gender= '女'),
-- 	CONSTRAINT	fk	FOREIGN KEY(major_id)	REFERENCES major_info(id)
-- );

/*

主键和唯一
主键不为空
主键少于等于一个
两者都可以组合，但不推荐

外键
需要在从表中设置
关联的列类型一致或兼容
主表关联的列必须是key(主键或一致)

插入外键时先主后从
删除外键时先从后主

标识列
需要和一个键搭配
只能有一个
必须是数值
可以设置步长和起始值
*/

-- SET auto_increment_increment=3;
-- SET auto_increment_offset=10;
-- show variables like '%auto_inc%';



