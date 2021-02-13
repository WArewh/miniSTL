#ifndef BEHAVIORAL_OBSERVER_OBSERVER_H_
#define BEHAVIORAL_OBSERVER_OBSERVER_H_

#include <vector>
using std::vector;

// 推送观察者
class PushObserver {
public:
    virtual void getUpdate();
};


class User : public PushObserver {
public:
    void getUpdate();

private:
};


// 主播
class Anchor {
public:
    void StartLive();

private:
    vector<PushObserver*> m_subscriptVec;// 那些人订阅了主播
};

void Anchor::StartLive() {
    // 推送
    for (auto obj : m_subscriptVec) {
        obj->getUpdate();
    }
}

#endif