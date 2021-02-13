#ifndef CREATIONAL_BUILDER1_BUILDER_H_
#define CREATIONAL_BUILDER1_BUILDER_H_

#include "stage2.h"

class HouseDirector;

// 构建部分
class HouseBuilder {
    // 不设为纯虚函数，是因为房子可以按照默认的方法进行生成，重写方法即可自定义生成房子
    friend class HouseDirector;

private:
    virtual void InstallDoor();
    virtual void InstallWall();
    virtual void InstallWindows();
    virtual void DesignRoom();
    House* build() { return m_house; }

private:
    House* m_house;
};

//组合部分，因为单一职责这一条原则因此没写进builder里，直接写进builder也可以
class HouseDirector {
public:
    HouseDirector(HouseBuilder* builder) : m_builder(builder) {}
    House* Construct();

private:
    HouseBuilder* m_builder;
};

House* HouseDirector::Construct() {
    m_builder->InstallDoor();
    m_builder->InstallWall();
    m_builder->InstallWindows();
    m_builder->DesignRoom();
    return m_builder->build();
}

#endif