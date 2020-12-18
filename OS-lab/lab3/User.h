#ifndef LAB_USER_H_
#define LAB_USER_H_

#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "folder.h"

using std::equal_to;
using std::hash;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;

const uint32_t U_MAX_LENGTH = 14;

class UserManager;
class FileSystem;

class User {
    friend class UserManager;
    friend class FileSystem;

public:
    User() : m_name(""), m_password(""), m_index(-1) {}
    User(string name, string password);
    User(string name, string password, uint32_t index);
    ~User();
    const char* name() const { return m_name; }

private:
    char m_name[U_MAX_LENGTH];
    char m_password[U_MAX_LENGTH];
    uint32_t m_index;  // inode号
};

struct UserInfo {
    shared_ptr<User> m_data;
    shared_ptr<Folder> m_folder;
    UserInfo() : m_data(nullptr), m_folder(nullptr) {}
    UserInfo(shared_ptr<User> data, shared_ptr<Folder> folder) : m_data(data), m_folder(folder) {}
};

#endif