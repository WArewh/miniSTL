#ifndef CREATIONAL_ABSTRACTFACTORY_ABSTRACTFACTORY_H_
#define CREATIONAL_ABSTRACTFACTORY_ABSTRACTFACTORY_H_

#include "stage4.h"

// 抽象工厂
class AbstractMazeFactory {
public:
    AbstractMazeFactory();
    virtual Maze* MakeMaze();
    virtual Wall* MakeWall();
    virtual Room* MakeRoom(int num);
    virtual Door* MakeDoor(Room* r1, Room* r2);
    // add stage4

    virtual Ornament* MakeOrnament(Room*);

    // end
};

// 具体工厂 一般为单例模式：即全局唯一
class LargeMazeFactory : public AbstractMazeFactory {
public:
    virtual Maze* MakeMaze() const { return new LargeMaze(); }
    virtual Wall* MakeWall() const { return new IronWall(); }
    virtual Room* MakeRoom(int num) { return new BossRoom(num); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new IronDoor(r1, r2); }
    // add stage4

    virtual Ornament* MakeOrnament(Room* r1) const { return new IronOrnament(r1); }

    // end
};

class MiddleMazeFactory : public AbstractMazeFactory {
public:
    virtual Maze* MakeMaze() const { return new MiddleMaze(); }
    virtual Wall* MakeWall() const { return new StoneWall(); }
    virtual Room* MakeRoom(int num) { return new EliteRoom(num); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new StoneDoor(r1, r2); }
    // add stage4

    virtual Ornament* MakeOrnament(Room* r1) const { return new StoneOrnament(r1); }

    // end
};

class LittleMazeFactory : public AbstractMazeFactory {
public:
    virtual Maze* MakeMaze() const { return new LittleMaze(); }
    virtual Wall* MakeWall() const { return new WoodenWall(); }
    virtual Room* MakeRoom(int num) { return new BossRoom(num); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new WoodenDoor(r1, r2); }
    // add stage4

    virtual Ornament* MakeOrnament(Room* r1) const { return new WoodenOrnament(r1); }

    // end
};

// add stage3

class HugeMazeFactory : public AbstractMazeFactory {
public:
    virtual Maze* MakeMaze() const { return new HugeMaze(); }
    virtual Wall* MakeWall() const { return new CrystalWall(); }
    virtual Room* MakeRoom(int num) { return new CrystalRoom(num); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const { return new CrystalDoor(r1, r2); }
    // add stage4

    virtual Ornament* MakeOrnament(Room* r1) const { return new CrystalOrnament(r1); }

    // end
};

// End


class MazeTester {
public:
    MazeTester();
    Maze* TestMaze1(AbstractMazeFactory& f);  //创建布局1
    //...
private:
};

//一种实现
Maze* MazeTester::TestMaze1(AbstractMazeFactory& f) {

    Maze* m1 = f.MakeMaze();
    Room* r1 = f.MakeRoom(1);
    Room* r2 = f.MakeRoom(2);
    Door* d1 = f.MakeDoor(r1, r2);
    // add stage4

    Ornament* o1 = f.MakeOrnament(r1);

    // end
    r1->setSide(East, d1);
    r2->setSide(West, d1);
    //...
    return m1;
}


#endif