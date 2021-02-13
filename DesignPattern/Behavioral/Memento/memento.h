#ifndef BEHAVIORAL_MEMENTO_MEMENTO_H_
#define BEHAVIORAL_MEMENTO_MEMENTO_H_

#include <stack>

using std::stack;

// 接口

class Chess {
public:
    //...
private:
    int x, y;
};
// End

class ChessMemento {
public:
private:
    int x, y;
};

class ChessCaretaker {
public:
    void save(ChessMemento*);
    ChessMemento* load();

private:
    stack<ChessMemento*> m_mem;  // 记录每一步棋子的位置
};

#endif