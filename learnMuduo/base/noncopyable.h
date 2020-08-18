#ifndef BASE_NONCOPYABLE_H_
#define BASE_NONCOPYABLE_H_

/*
 * 空类，继承它的类不能使用拷贝构造函数和赋值构造函数
 * 空基类优化(Day1)
 */
namespace myNet {
    class noncopyable {
    public:
        noncopyable(const noncopyable&) = delete;
        void operator=(const noncopyable&) = delete;

    protected:
        noncopyable() = default;
        ~noncopyable() = default;
    };
}  // namespace myNet

#endif