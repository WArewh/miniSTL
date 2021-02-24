# 背景
小W加入到一个点餐App的项目中，其中你得到的任务是提供不同的付款渠道，计算不同的折扣，进行扣款

# solution
可以使用if-else结构
```
if(支付宝)
    支付宝.pay()
else if(微信)
    微信.pay()
//... 其他支付方式
```
如果要对支付手段进行增删改，就容易出现错误，因此需要将if-else消灭  
定义一个支付接口，让支付手段类实现此方法，再写一个支付类，调用支付手段，具体见strategy.h  

# notes
支付手段类一般为单例，可以配合享元模式和工厂方法，具体见notes.h