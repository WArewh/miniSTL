/*

覆盖索引:只用索引就查到所要的内容

EXPLAIN id select_type table type possilbe_key key key_len ref rows filtered extra

id 执行顺序
相同 从上到下
不同 id越大优先级越高

select_type 查询的类型
simple
primary
subquery
derived
union
union result

table			来自哪里

type			访问类型
system>const>eq_ref>ref>range>index>all

possible_key 	可能用到的索引

key				用到的索引(覆盖索引不出现possible key)

key_len			使用到的索引长度有多少字节

ref				索引那一列或者常量被使用了

rows			读取的行数

filtered 		返回结果的行占需要读到的行(rows列的值)的百分比

extra			额外信息
using filesort	会对数据进行外部排序(没有完全利用到了索引)
using temporary 使用了临时表(查询结果排序)
using index 	使用到了索引，同时出现using where执行了索引键值查找,没有则只是读取
using where		where过滤

*/

/*

单表索引优化

1.查啥建啥
2.最佳左前缀(复合索引建立是一层一层的，如果有一层没有匹配则后面失效)
3.不要在索引列上进行操作(可能会导致索引失效),比如left(name,3)
4.最右边索引失效,调整索引字段的顺序,将范围字段放到前面
5.使用不等于或NOT NULL索引失效，尽量找代替
6.like以通配符开始索引失效，尽量避免

*/

/*

多表索引优化
关联查询,全表扫描的是驱动表,另一个表叫被驱动表

1.给被驱动表建索引而不是驱动表，让小表当驱动表，大表当被驱动表
2.使用Inner join,mysql会自己选择最优策略
3.子查询尽量不要放在被驱动表里
4.能多表关联就多表关联，不使用子查询

*/

/*

子查询优化：不要使用否定，使用外查询

*/

/*

排序分组优化:

外部排序：有两种排序方式单路(访问一次磁盘，在内存buffer里排序)和双路(访问两次磁盘，在磁盘里排序),因此小数据单路好,大数据双路好

ORDER BY
外部排序出现场合:不过滤、顺序错、方向反

GROUP BY
外部排序出现场合:顺序错、方向反

*/

/*

*/