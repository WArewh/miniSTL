# StringPiece的作用
这个类实现了高效的字符串传递以及对字符串的代理,通常叫做string view。  
它提供了一个窗口，外部仅可以观察到这个窗口中字符串的内容，在调整窗口大小时不需要修改原字符串，仅移动开始指针和调整长度即可。  
另外这个类自身并不存储这个字符串，所以它的有效生存期取决于源字符串指针的生存期。

# 为什么能高效的传递
string源码 https://zhuanlan.zhihu.com/p/157169295?from_voters_page=true

在传递一个长度很长的const char *的时候会进行拷贝，导致产生一个比较大的字符串对象，但StringPiece仅仅是传递指针，因此高效。

# 宏实现函数重载
```
#define STRINGPIECE_BINARY_PREDICATE(cmp,auxcmp)                             \
  bool operator cmp (const StringPiece& x) const {                           \
    int r = memcmp(ptr_, x.ptr_, length_ < x.length_ ? length_ : x.length_); \
    return ((r auxcmp 0) || ((r == 0) && (length_ cmp x.length_)));          \
  }
  STRINGPIECE_BINARY_PREDICATE(<,  <);
  STRINGPIECE_BINARY_PREDICATE(<=, <);
  STRINGPIECE_BINARY_PREDICATE(>=, >);
  STRINGPIECE_BINARY_PREDICATE(>,  >);
#undef STRINGPIECE_BINARY_PREDICATE
```