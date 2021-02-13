#ifndef CREATIONAL_BUILDER2_STAGE1_H_
#define CREATIONAL_BUILDER2_STAGE1_H_

#include <string>

using std::string;

class User {
public:
    User(string username, string password);
    User(string username, string password, string nickname);

private:
    string m_username;
    string m_password;
    string m_nickname;
};

#endif