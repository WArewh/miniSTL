#ifndef LAB_USER_MANAGER_H_
#define LAB_USER_MANAGER_H_

#include <stack>

#include "User.h"
#include "disk.h"

const uint32_t USR_SIZE = 32;
const uint32_t U_START = 1 * BLOCK_SIZE;
const uint32_t U_MAX_COUNT = BLOCK_SIZE / USR_SIZE - 1;
const uint32_t U_END = U_START + U_MAX_COUNT * USR_SIZE;

class UserManager
{
public:
    UserManager(Disk&);
    ~UserManager();

public:
    bool add(shared_ptr<User> ptr);
    bool erase(shared_ptr<User> ptr);
    bool authentication(shared_ptr<User>& ptr);

private:
    void initTable();

private:
    Disk disk;
    unordered_map<string, shared_ptr<User>> m_table;
    uint32_t m_table_size;
};

#endif