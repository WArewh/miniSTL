-- 查询

-- 单个字段
-- SELECT last_name FROM employees;

-- 多个字段
-- SELECT last_name,first_name FROM employees;

-- 所有字段
-- SELECT * FROM employees;

-- 函数
-- SELECT VERSION();

-- 起别名(特殊情况使用"")
-- SELECT last_name AS 姓,first_name AS 名 FROM employees;
-- SELECT last_name 姓,first_name 名 FROM employees;

-- 去重
-- SELECT DISTINCT department_id FROM departments;

-- SELECT CONCAT(last_name," ",first_name) AS 姓名 FROM employees;



-- 条件查询 <>不等于

-- SELECT * FROM employees WHERE salary > 12000
-- SELECT last_name,department_id FROM employees WHERE department_id = 90;

-- SELECT * FROM employees WHERE salary >= 10000 AND salary <= 20000;


-- 模糊查询
-- % 任意多个字符 _一个任意单个字符	特殊情况使用转义

-- SELECT * FROM employees WHERE last_name LIKE '%a%';

-- SELECT * FROM employees WHERE last_name LIKE '__n_l%';

-- SELECT * FROM employees WHERE last_name LIKE '_\_%';
-- SELECT * FROM employees WHERE last_name LIKE '_$_%' ESCAPE '$';

-- 包含临界 BETWEEN 大于等于 AND 小于等于 
-- SELECT * FROM employees WHERE salary BETWEEN 10000 AND 20000;

-- SELECT * FROM employees WHERE job_id IN('IT_PROG','AD_VP');

-- SELECT * FROM employees WHERE commission_pct IS NULL;
-- SELECT * FROM employees WHERE commission_pct IS NOT NULL;

-- 安全等于 <=>
-- SELECT * FROM employees WHERE commission_pct<=>NULL;
-- SELECT * FROM employees WHERE salary <=> 12000;


-- 排序查询
-- SELECT * FROM employees WHERE salary BETWEEN 10000 AND 20000 ORDER BY salary ASC;
-- SELECT * FROM employees WHERE salary BETWEEN 10000 AND 20000 ORDER BY hiredate DESC;
-- SELECT *,salary*12*(1+IFNULL(commission_pct,0)) AS 年薪 FROM employees ORDER BY 年薪 DESC;
-- SELECT * FROM employees ORDER BY salary DESC,job_id ASC;--多字段

-- if 
-- SELECT *,if(commission_pct IS NULL ,"没有奖金","有奖金") AS 备注 FROM employees 

-- case 
-- SELECT department_id,salary AS 工资,
-- CASE department_id
-- 	WHEN 30 THEN salary*1.1
-- 	WHEN 40 THEN salary*1.2
-- 	WHEN 50 THEN salary*1.3
-- ELSE salary 
-- END AS 新工资 
-- FROM employees;

-- SELECT salary,
-- CASE
-- 	WHEN salary>=20000 THEN 'A'
--     WHEN salary>=15000 THEN 'B'
-- 	WHEN salary>=10000 THEN 'C'
-- 	ELSE 'D'
-- END AS 工资级别
-- FROM employees;

-- 分组查询

-- SELECT COUNT(*),location_id FROM departments GROUP BY location_id;

-- SELECT FROM WHERE(字段) GROUP BY ORDER BY

-- SELECT job_id 工种,AVG(salary) 平均工资 
-- FROM employees 
-- WHERE salary BETWEEN 1000 AND 8000 
-- GROUP BY job_id 
-- ORDER BY AVG(salary) ASC;

-- SELECT MAX(salary*(1+commission_pct)) 最大工资,manager_id 
-- FROM employees 
-- WHERE commission_pct IS NOT NULL 
-- GROUP BY manager_id 
-- ORDER BY MAX(salary) DESC;


-- SELECT FROM WHERE GROUP BY HAVING(GROUP BY的结果上筛选) ORDER BY
-- SELECT department_id 部门,COUNT(*) 个数 
-- FROM employees 
-- WHERE department_id>50
-- GROUP BY department_id
-- HAVING COUNT(*)>2
-- ORDER BY COUNT(*) DESC;

-- 多表查询
-- 内连接sql92 sql99

-- 等值
-- SELECT *
-- FROM employees,departments 
-- WHERE employees.department_id = departments.department_id;

-- SELECT last_name,department_name
-- FROM employees e
-- INNER JOIN departments d
-- ON e.department_id = d.department_id;

-- 非等值
-- SELECT salary,grade_level
-- FROM employees,job_grades
-- WHERE salary BETWEEN job_grades.lowest_sal AND job_grades.highest_sal
-- ORDER BY grade_level ASC;

-- SELECT salary,grade_level
-- FROM employees
-- INNER JOIN job_grades
-- WHERE salary BETWEEN job_grades.lowest_sal AND job_grades.highest_sal
-- ORDER BY grade_level ASC,salary ASC;

-- 自连接
-- SELECT e.employee_id,e.last_name,m.employee_id,m.last_name
-- FROM employees e,employees m
-- WHERE e.employee_id = m.manager_id;

-- SELECT e.employee_id,e.last_name,m.employee_id,m.last_name
-- FROM employees e
-- INNER JOIN employees m
-- WHERE e.employee_id = m.manager_id;

-- 外连接:一个表有，另一个表没有的记录 sql99
-- 结果:主表+没有的记录

-- 左外连接

-- SELECT d.*,e.department_id
-- FROM departments d
-- LEFT OUTER JOIN employees e
-- on e.department_id = d.department_id

-- 右外连接
-- SELECT d.*,e.department_id
-- FROM employees e
-- RIGHT OUTER JOIN departments d
-- on e.department_id = d.department_id

-- 全外连接
-- 略 内连接+表一有表二没有+表一没有表二有

-- 交叉接连  笛卡尔乘积
-- SELECT d.*,e.department_id
-- FROM employees e
-- CROSS JOIN departments d

-- 子查询(内查询) 其他语句的select

-- where后面
-- 标量子(一行一列)
-- SELECT *
-- FROM employees
-- WHERE salary>(
-- 	SELECT salary
-- 	FROM employees
-- 	WHERE last_name = 'Abel'
-- );

-- SELECT *
-- FROM employees
-- WHERE 
-- job_id=(
-- 	SELECT job_id
-- 	FROM employees
-- 	WHERE employee_id=141
-- )
-- AND
-- salary>(
-- 	SELECT salary
-- 	FROM employees
-- 	WHERE employee_id=143
-- );


-- 多行查询(列子查询)
-- SELECT last_name 
-- FROM employees
-- WHERE department_id IN(
-- 	SELECT DISTINCT department_id 
-- 	FROM departments 
-- 	WHERE location_id IN(1400,1700)
-- );

-- 多列查询(行子查询)
-- SELECT * 
-- FROM employees
-- WHERE employee_id=(
-- 	SELECT MIN(employee_id)
-- 	FROM employees
-- )
-- AND
-- salary=(
-- 	SELECT MAX(salary)
-- 	FROM employees
-- );

-- SELECT * 
-- FROM employees
-- WHERE (employee_id,salary)=(
-- 	SELECT MIN(employee_id),MAX(salary)
-- 	FROM employees
-- );


-- select后面
-- SELECT d.*,
-- (
-- 	SELECT COUNT(*)
-- 	FROM employees e
-- 	WHERE e.department_id=d.department_id
-- ) 个数
-- FROM departments d;

-- from后面
-- SELECT avg_dep.*,g.grade_level
-- FROM (
-- 	SELECT AVG(salary) avg,department_id dep
-- 	FROM employees
-- 	GROUP BY department_id
-- )avg_dep
-- INNER JOIN job_grades g
-- ON avg_dep.avg BETWEEN lowest_sal AND highest_sal;

-- exist(相关子查询)过滤 
-- SELECT department_name
-- FROM departments d
-- WHERE EXISTS(
-- 	SELECT *
-- 	FROM employees e
-- 	WHERE d.department_id=e.department_id
-- );

-- 分页查询
-- SELECT *
-- FROM employees
-- LIMIT 5,5;-- offset,size


-- 联合查询
-- SELECT * FROM employees WHERE email LIKE "%a%"
-- UNION
-- SELECT * FROM employees WHERE department_id > 90;


