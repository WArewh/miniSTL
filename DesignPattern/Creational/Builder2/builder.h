#ifndef CREATIONAL_BUILDER2_BUILDER_H_
#define CREATIONAL_BUILDER2_BUILDER_H_

#include "stage3.h"
// Builder 一般为单例
class UserBuilder {
public:
    UserBuilder* username(string username) {
        m_username = username;
        return this;
    }
    UserBuilder* password(string password) {
        m_password = password;
        return this;
    }
    //...
    User* build() { return new User(this); }

private:
    string m_username;
    string m_password;
    string m_nickname;

    // add stage2

    char m_sex;
    int m_age;
    string m_area;
    string m_signature;
    string m_phone;
};


// 创建一个对象
void CREATIONALUser() {
    auto builder = new UserBuilder();
    User* usr = builder->username("xxx")->password("xxx")->build();
}

#endif