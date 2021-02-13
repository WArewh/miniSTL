#ifndef CREATIONAL_ABSTRACTFACTORY_STAGE3_H_
#define CREATIONAL_ABSTRACTFACTORY_STAGE3_H_

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

// add stage3

class CrystalRoom : public Room {
public:
    CrystalRoom(int roomNo);
    virtual void Enter();
};

// End

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

// Add stage2

class WoodenWall : public Wall {
public:
    WoodenWall();
    virtual void Enter();
};

class StoneWall : public Wall {
public:
    StoneWall();
    virtual void Enter();
};

class IronWall : public Wall {
public:
    IronWall();
    virtual void Enter();
};

// End

// add stage3

class CrystalWall : public Wall {
public:
    CrystalWall();
    virtual void Enter();
};

// End

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

// Add stage2

class WoodenDoor : public Door {
public:
    WoodenDoor(Room*, Room*);
    virtual void Enter();
};

class StoneDoor : public Door {
public:
    StoneDoor(Room*, Room*);
    virtual void Enter();
};

class IronDoor : public Door {
public:
    IronDoor(Room*, Room*);
    virtual void Enter();
};

// End

// add stage3

class CrystalDoor : public Door {
public:
    CrystalDoor(Room*, Room*);
    virtual void Enter();
};

// End

//抽象基类
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

// add stage3

class HugeMaze : public Maze {
public:
    HugeMaze();
};

// end

#endif