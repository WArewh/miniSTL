#ifndef BEHAVIORAL_STRATEGY_NOTES_H_
#define BEHAVIORAL_STRATEGY_NOTES_H_
#include <string>
#include <unordered_map>

template <class T>
class Singleton {
public:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    virtual ~Singleton() = default;

public:
    static T& GetInstance() {
        static T s_instance;
        return s_instance;
    }
};

enum class PayStrategyCode
{
    Ali,
    WeChat,
};


class PayStrategy {
public:
    virtual double pay() = 0;
};

class Alipay : public PayStrategy, public Singleton<Alipay> {
public:
    double pay();
};

class Wepay : public PayStrategy, public Singleton<Alipay> {
public:
    double pay();
};

//...

class PayContent : Singleton<PayContent> {
private:
    PayStrategy* m_strategy;

public:
    PayContent(PayStrategy* strategy) : m_strategy(strategy) {}

public:
    double cal() { return m_strategy->pay(); }
};


using std::unordered_map;

class PayStrategyFactory : public Singleton<PayStrategyFactory> {
public:
    void add(PayStrategyCode code, PayStrategy* st);
    void remove(PayStrategyCode code);
    PayStrategy* get(PayStrategyCode code);

private:
    unordered_map<PayStrategyCode, PayStrategy*> m_factory;
};

// End


#endif