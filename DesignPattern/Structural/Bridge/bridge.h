#ifndef STRUCTURAL_BRIDGE_BRIDGE_H_
#define STRUCTURAL_BRIDGE_BRIDGE_H_

class Quality {};

class WeaponType {};

class Weapon {
public:
    virtual void attack();

private:
    //抽象部分，具体实现派生基类即可

    Quality* m_quality;
    WeaponType* m_type;
    int damage;
};

class WhiteQuality : public Quality {};

//...

class Sword : public WeaponType {};

//...

#endif