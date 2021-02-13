#ifndef CREATIONAL_BUILDER1_STAGE1_H_
#define CREATIONAL_BUILDER1_STAGE1_H_

class Door {};

class Wall {};

class Windows {};

class Room {};

class House {
public:
    virtual void init();

protected:
    virtual void InstallDoor();
    virtual void InstallWall();
    virtual void InstallWindows();
    virtual void DesignRoom();
    //...
};

void House::init() {  // 不能在构造函数写虚函数
    InstallDoor();
    InstallWall();
    InstallWindows();
    DesignRoom();
}

#endif