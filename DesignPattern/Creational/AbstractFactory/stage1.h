#ifndef CREATIONAL_ABSTRACTFACTORY_STAGE1_H_
#define CREATIONAL_ABSTRACTFACTORY_STAGE1_H_

#include <vector>  //储存Maze

class RoomEdge;  //前向声明

enum Direction
{
    North,
    South,
    East,
    West,
};

//抽象基类
class Room {
public:
    Room(int roomNo);
    RoomEdge* GetSide() const;
    void setSide(Direction, RoomEdge*);

protected:
    RoomEdge* m_sides[4];
    int m_number;
};

class CommonRoom : public Room {
public:
    CommonRoom(int roomNo);
};

class EliteRoom : public Room {
public:
    EliteRoom(int roomNo);
};

class BossRoom : public Room {
public:
    BossRoom(int roomNo);
};

//抽象基类
class RoomEdge {
public:
    //进入产生的效果，比如，进入墙，则不会产生任何效果，进入打开的门则会进入下一个房间，
    virtual void Enter() = 0;
};

class Wall : public RoomEdge {
public:
    Wall();
    virtual void Enter();
};

class Door : public RoomEdge {
public:
    Door(Room*, Room*);
    Room* OtherSideRoom(Room*);
    virtual void Enter();

protected:
    Room* m_room1;
    Room* m_room2;
    bool m_isOpen;
};

class Maze {
public:
    //尺寸通过resize实现
    Maze();
    void addRoom(Room*);

private:
    std::vector<std::vector<Room*>> m_map;
};

//实现类
class LargeMaze : public Maze {
public:
    LargeMaze();
};

class MiddleMaze : public Maze {
public:
    MiddleMaze();
};

class LittleMaze : public Maze {
public:
    LittleMaze();
};


class MazeTester {
public:
    MazeTester();
    Maze* CREATIONALTestMaze1();  //创建布局1
    //...
private:
};

//一种实现
Maze* MazeTester::CREATIONALTestMaze1() {

    //硬编码，固定死了，对其它的类进行测试就要修改代码
    Maze* m1 = new Maze();
    Room* r1 = new CommonRoom(1);
    Room* r2 = new BossRoom(2);
    Door* d1 = new Door(r1, r2);

    m1->addRoom(r1);
    m1->addRoom(r2);

    r1->setSide(East, d1);
    r2->setSide(West, d1);
    //...
    return m1;
}

#endif