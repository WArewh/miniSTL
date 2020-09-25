-- 插入

-- 方式一
-- INSERT INTO 
-- job_grades(grade_level,lowest_sal,highest_sal)
-- VALUES('G',40000,60000);

-- 支持子查询
-- INSERT INTO 
-- job_grades(grade_level,lowest_sal,highest_sal)
-- SELECT * FROM job_grades WHERE grade_level<'D';


-- 方式二
-- INSERT INTO 
-- job_grades 
-- SET grade_level='G',lowest_sal=40000,highest_sal=60000;

-- 修改
-- UPDATE job_grades
-- SET highest_sal=39999
-- WHERE highest_sal=40000;

-- 多个表使用外查询

-- 删除
-- DELETE FROM job_grades WHERE highest_sal=60000;
-- TRUNCATE 删表 

-- 库的管理
-- CREATE DATABASE IF NOT EXISTS books;
-- DROP DATABASE IF EXISTS books;

-- 表的管理

-- 创建
-- CREATE TABLE 表名{
-- 	列名	类型[(长度)	约束]
-- };

-- 删除
-- DROP TABLE IF EXISTS 表名

-- 改
-- ALTER TABLE 表名 CHANGE COLUMN 旧名 新名	(类型)
-- ALTER TABLE 表名 MODIFY COLUMN 名字 类型	(修改添加约束)
-- ALTER TABLE 表名 ADD COLUMN 名字 类型
-- ALTER TABLE 表名 DROP COLUMN 名字 		(删除主键外键唯一)
-- ALTER TABLE 表名 RENAME TO 新表名;


-- 复制结构
-- CREATE TABLE 表名 LIKE 需要复制的表;

-- 复制结构数据
-- CREATE TABLE 表名
-- SELECT * FROM 需要复制的表;
