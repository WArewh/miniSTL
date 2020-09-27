# singleton的作用
实现单例模式，使用pthread_once

# 技巧

在编译期判断不完整的类，在date类也使用了类似的方法进行判断int的位数大小
```
typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    T_must_be_complete_type dummy; (void) dummy;
```

判断是否有no_destroy这个方法
```
struct has_no_destroy
{
  template <typename C> static char test(decltype(&C::no_destroy));
  template <typename C> static int32_t test(...);
  const static bool value = sizeof(test<T>(0)) == 1;
};
```