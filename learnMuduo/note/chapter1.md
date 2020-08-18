# Chapter1 线程安全的对象生命周期管理

## 知识点

### RALL
资源获取即初始化。使用对象管理资源，在构造函数里分配资源，在析构函数里释放资源

### 空基类优化
一个空类(没有non-static数据成员的类)的大小一般为1，以此来标识对象  
使用聚合会让类的大小+1，如果再有对齐限制，会导致空间的浪费  
使用继承，只要不与同一类型的另一个对象或子对象分配同一地址(两个对象不能占用同一地址)，就不需为其分配任何空间。

### 创建对象
不要把this指针泄漏给其他对象，如果泄漏，可能会让其他对象访问一个半成品的对象，可以使用构造+init

### 销毁对象
使用智能指针
如果析构比较耗时可以使用将这个对象加入队列，用另一个线程执行析构

### 避免指针错误的方法
缓冲区溢出:vector和string或自己写的buffer class  
空悬指针/野指针:智能指针  
重复释放/内存泄漏:ptr放进对象，析构自动释放  
不匹配的new/delete[]:替换成vector/array

### enable_shared_from_this
首先来看这个例子
```
class Bad
{
public:
	std::shared_ptr<Bad> getptr() {
		return std::shared_ptr<Bad>(this);
	}
	~Bad() { std::cout << "Bad::~Bad() called" << std::endl; }
};

int main()
{
	// 错误的示例，每个shared_ptr都认为自己是对象仅有的所有者
	std::shared_ptr<Bad> bp1(new Bad());
	std::shared_ptr<Bad> bp2 = bp1->getptr();
	// 打印bp1和bp2的引用计数
	std::cout << "bp1.use_count() = " << bp1.use_count() << std::endl;// 1
	std::cout << "bp2.use_count() = " << bp2.use_count() << std::endl;// 1
    //释放两次
}  
```
执行后use_count全部为1，释放了两次，面对这种情况我们想要这个shared_ptr的对象，使得use_count为2，可以使用下面的方法
```
class Good : std::enable_shared_from_this<Good>//继承
{
public:
	std::shared_ptr<Good> getptr() {
		return shared_from_this();//使用这个方法
	}
	~Good() { std::cout << "Good::~Good() called" << std::endl; }
};
int main()
{
	std::shared_ptr<Good> gp1(new Good());
	std::shared_ptr<Good> gp2 = gp1->getptr();
	// 打印gp1和gp2的引用计数
	std::cout << "gp1.use_count() = " << gp1.use_count() << std::endl;
	std::cout << "gp2.use_count() = " << gp2.use_count() << std::endl;
} 
```
其实这个enable_shared_from_this类包含了一个weak_ptr，通过weak_ptr我们就得到了这个shared_ptr的对象，通过这个办法来实现保活机制

### 弱回调
对象活着调用成员函数，死了忽略

### 智能指针特性
析构动作在创建时被捕获，意味着
- 虚析构不再是必须(创建对象时保存了子类的指针类型)
- 安全跨越模块
- 二进制兼容(暂时没看懂)
- 析构动作可以定制(删除器)

### 智能指针注意事项
- 定义对象时使用shared_ptr，其他地方引用对象时使用weak_ptr。因为会出现循环引用或者延长对象生命周期的问题
- shared_ptr的引用计数本身是安全且无锁的，但它有两个数据成员(ptr和count)，因此对对象的修改是没有原子性的，比如
```
int*p=new int
shared_ptr<int>p1(p);
shared_ptr<int>p2=p1;
// p2=p1需要修改count并且让p2.ptr指向p 这不是原子的
// 因此多线程读写对shared_ptr是要加锁的
```
- weak_ptr可以做弱回调和对象池



## 拓展

### 从汇编层面看引用和指针
```
//使用的指令为g++ -S
int a = 10;
// movl	$10, -12(%rbp)  a的地址为R[%rbp]-12的内容
int &b = a;
// leaq	-12(%rbp), %rax rax为a的地址
// movq	%rax, -8(%rbp)  b的地址为R[%rbp]-8的内容,存储a的地址
b = 20;
// movq	-8(%rbp), %rax  rax为b的地址
// movl	$20, (%rax)     M[rax]即a和b的地址=20
```
可以看出引用和指针在汇编层面上没有什么不同，引用的实现就是指针。因此int&b=20编译报错，是因为20是立即数不能取地址。那么const int&=20为什么可以通过编译且可以正常运行呢?
```
const int &a = 20;
// movl	$20, %eax
// movl	%eax, -12(%rbp)
// leaq	-12(%rbp), %rax
// movq	%rax, -8(%rbp)
```
可以发现const int&之所以可以指向常量是因为编译器自动生成了一个临时变量让20这个数有地址可取，但不能对其进行修改。再来看看右值引用。
```
int &&a = 20;
// movl	$20, %eax
// movl	%eax, -12(%rbp)
// leaq	-12(%rbp), %rax
// movq	%rax, -8(%rbp)
```
可以知道常量引用和右值引用在汇编层面上也是相同的，而且右值引用可以进行写操作

### 右值引用的好处
右值引用可以得到临时对象并且可以对临时对象进行修改，可以想到临时对象的创建往往和拷贝构造有关
先来看看拷贝构造函数发生的时机  
- 用创建好的对象初始化另一个对象  
- 值传递给函数参数  
- 局部对象作为返回值(一般会优化)  
可以发现有些时候其实可以不用拷贝构造,比如
```
vector<string>vec;
/虽然传递的是const char*,但是会通过string(const char*)的构造函数构造出string
vec.push_back("aaa");
```
没有右值引用会使用拷贝构造函数，由于字符串可能很长会导致效率低下，如果使用右值引用只需要将string的指针给到需要的对象，大大提高了对象的使用效率




