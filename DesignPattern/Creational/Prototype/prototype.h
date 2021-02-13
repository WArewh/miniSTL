#ifndef CREATIONAL_PROTOTYPE_PROTOTYPE_H_
#define CREATIONAL_PROTOTYPE_PROTOTYPE_H_

class Prototype {
    virtual Prototype* clone();
};

class Zombies : Prototype {
public:
    virtual void attack();
    // add

    virtual Prototype* clone() { return new Zombies(*this); }
    // end
private:
    Zombies(const Zombies& zombies);

private:
    int m_health;
    int m_damage;
    //...
};

//...


#endif