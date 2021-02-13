#ifndef BEHAVIORAL_STRATEGY_STRATEGY_H_
#define BEHAVIORAL_STRATEGY_STRATEGY_H_

class PayStrategy {
public:
    virtual double pay() = 0;
};

class Alipay : public PayStrategy {
public:
    double pay();
};

class Wepay : public PayStrategy {
public:
    double pay();
};

//...

class PayContent {
private:
    PayStrategy* strategy;

public:
    double cal() { return strategy->pay(); }
};


#endif