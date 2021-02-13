#ifndef CREATIONAL_BUILDER2_STAGE2_H_
#define CREATIONAL_BUILDER2_STAGE2_H_

#include <string>

using std::string;

class User {
public:
    User(string username, string password);

    // Add stage2

    void getName();
    void setName(string name);
    //...

    // End

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