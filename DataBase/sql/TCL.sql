/*

事务:一组sql语句组成的执行单元
事务失败则回滚
事务具有原子性、一致性、隔离性、持久性

并发问题：
脏读:在一个事务没有提交之前，另一个事务看到的内容改变
不可重复读:在一个事务提交之后，另一个事务看到的内容改变
幻读:一个事务插入了字段，另一个事务看到的内容改变

隔离级别从低到高依次可以解决上面的三个问题
READ UNCOMMITTED
READ COMMITTED
REPEATABLE READ
SERIALIZABLE

查看隔离级别
select @@transaction_isolation;

修改隔离级别
set transaction isolation level 隔离级别
*/

-- 隐式事务:INSERT DELETE UPDATE等
-- 显式事务:必须要自动提交关闭

-- SET autocommit=0;
-- START TRANSACTION
-- sql语句
-- SAVEPOINT 名字;(搭配ROLLBACK TO)
-- COMMIT/ROLLBACK/ROLLBACK TO 保存点;

-- DELETE可回滚 TRUNCATE不可回滚

/*

视图(类似函数需要先创建)
虚拟表,通过表动态生成的数据，只保存sql逻辑，不保存查询结果

*/

-- 创建并使用
-- CREATE VIEW getName
-- AS
-- SELECT last_name,first_name 
-- FROM employees;
-- 
-- SELECT *
-- FROM getName;

-- 修改视图

-- CREATE OR REPLACE VIEW 视图名 AS sql语句
-- ALTER VIEW 视图名 AS sql语句

-- 删除视图
-- DROP VIEW 视图名;

-- 显示视图
-- show table status where comment='view';

-- DESC 视图名;

-- SHOW CREATE VIEW 视图名;

-- 更新(和表基本一样,修改的视图对应的表会同步)
-- 有些视图不能更新 
-- 视图中有表中没有的数据例如max(salary)
-- 常量视图
-- SELECT包含子查询
-- WHERE的子查询引用from的表

-- CREATE VIEW getMaxSalary
-- AS
-- SELECT max(salary)
-- FROM employees;
-- 
-- SELECT *FROM getMaxSalary;
-- 
-- INSERT INTO getMaxSalary VALUES(30000);

/*

变量
系统变量
	全局变量
	会话变量
自定义变量
	用户变量
	局部变量

*/

-- 全局变量显示 会话同理
-- SHOW GLOBAL VARIABLES;
-- SELECT @@GLOBAL.autocommit;
-- SET @@GLOBAL.autocommit=1;

-- 用户变量:针对当前会话
-- SET @name:="john";
-- SELECT @name;

-- SELECT MAX(salary) 
-- INTO @max_sal
-- FROM employees;
-- SELECT @max_sal;

-- 局部变量:BEGIN END中间且为第一句
-- DECLARE m INT DEFAULT 1;
-- DECLARE n INT DEFAULT 1;
-- DECLARE sum INT;
-- SET sum=m+n;
-- SELECT sum;


/*

存储过程
类似函数
仅有一条语句可不加begin end
过程的结尾使用delimter
参数模式
IN
OUT
INOUT

调用call

*/
-- CREATE PROCEDURE getMaxSal(OUT max_sal DOUBLE)
-- BEGIN
-- SELECT MAX(salary) 
-- FROM employees;
-- END;
-- 
-- call getMaxSal(@max_sal);
-- SELECT @max_sal;

-- 删除
-- DROP PROCEDURE IF EXISTS getMaxSal;

-- 查看
-- DESC 过程名;
-- SHOW CREATE PROCEDURE 过程名;

/*
函数

事务保存sql逻辑，返回一张虚拟的表
存储过程可以有多个返回值
函数只能有一个返回值

*/
-- SET GLOBAL log_bin_trust_function_creators=1;
-- 
-- CREATE FUNCTION getMaxSal() RETURNS DOUBLE
-- BEGIN
-- 	DECLARE max_sal DOUBLE DEFAULT 0; 
-- 	SELECT max(salary) 
-- 	INTO max_sal
-- 	FROM employees;
-- 	RETURN max_sal;
-- END;
-- 
-- SELECT getMaxSal();

-- 删除
-- DROP FUNCTION IF EXISTS getMaxSal;

-- 查看
-- DESC 过程名;
-- SHOW CREATE FUNCTION 过程名;

-- if函数 IF(expr1,expr2,expr3)

-- IF search_condition THEN statement_list
-- ELSEIF search_condition THEN statement_list
-- ELSE statement_list
-- END;

-- case 如果没有else且全部不匹配返回NULL
-- CASE case_value
-- 	WHEN when_value THEN
-- 		statement_list
-- 	ELSE
-- 		statement_list
-- END;

-- 循环
-- WHILE search_condition DO
-- 	statement_list
-- END;

-- label: LOOP
-- 	statement_list
-- 	IF exit_condition THEN
-- 		LEAVE label; 
-- 	END; 
-- END;

-- REPEAT
-- 	statement_list
-- UNTIL search_condition 
-- END;








