#ifndef BEHAVIORAL_STATE_STATE_H_
#define BEHAVIORAL_STATE_STATE_H_

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

// 单例(略)
class State;

// 主播
class Anchor {
public:
    void setState(State*);
    void StartLive();
    void PlayTape();

private:
    State* state;
    vector<PushObserver*> m_subscriptVec;  // 那些人订阅了主播
};

class State {
public:
    virtual void execute(Anchor&) = 0;
};

class StartLiveState : public State {
public:
    void execute(Anchor& anchor);
};

void StartLiveState::execute(Anchor& anchor) {
    anchor.StartLive();
}

class StopLiveState : public State {
public:
    void execute(Anchor& anchor);
};

void StopLiveState::execute(Anchor& anchor) {
    anchor.PlayTape();
}

#endif