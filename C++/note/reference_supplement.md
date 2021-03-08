# 右值引用和万能引用
- 引用的引用还是引用，只有右值引用的右值引用才是右值引用(右右为右)
- 针对右值引用使用move，对万能引用使用forward
- 避免使用万能引用重载
- 可以使用标签指派来解决万能引用重载问题
具体见[reference_supplement.cc](../base/reference_supplement.cc)

# 万能引用失败的情况
主要原因在于推导失败或者推导出错误结果，具体见[universal_reference.cc](../base/universal_reference.cc)