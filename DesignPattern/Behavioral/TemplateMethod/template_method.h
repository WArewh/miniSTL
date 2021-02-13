#ifndef BEHAVIORAL_TEMPLATEMETHOD_TEMPLATEMETHOD_H_
#define BEHAVIORAL_TEMPLATEMETHOD_TEMPLATEMETHOD_H_

class Animal {
public:
    void life();
    void dead() { isAlive = false; }
    virtual void eat() = 0;
    virtual void drink() = 0;

private:
    bool isAlive;
};

void Animal::life() {
    while (isAlive) {
        //子类重写方法即可
        eat();
        drink();
    }
}

#endif