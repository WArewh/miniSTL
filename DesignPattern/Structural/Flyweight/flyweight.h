#ifndef STRUCTURAL_FLYWEIGHT_FLYWEIGHT_H_
#define STRUCTURAL_FLYWEIGHT_FLYWEIGHT_H_

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
// 接口

class UserInfo {
public:
private:
    string m_name;
    string m_password;
};

// End


class UserInfoCache {
public:
    //...
private:
    unordered_map<string, UserInfo*> m_table;
};

#endif