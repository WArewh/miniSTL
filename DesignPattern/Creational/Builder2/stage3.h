#ifndef CREATIONAL_BUILDER2_STAGE3_H_
#define CREATIONAL_BUILDER2_STAGE3_H_

#include <string>

using std::string;

class UserBuilder;  //前向声明

class User {
public:
    User(string username, string password);
    User(const UserBuilder* builder);
    // delete all setter and getter


private:
    string m_username;
    string m_password;
    string m_nickname;

    // Add stage2

    char m_sex;
    int m_age;
    string m_area;
    string m_signature;
    string m_phone;

    // End
};


#endif