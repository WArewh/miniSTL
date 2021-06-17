#include "User_manager.h"

UserManager::UserManager(Disk& d) : disk(d)
{
    initTable();
}

void UserManager::initTable()
{
    disk.Read(U_END, &m_table_size, sizeof(uint32_t), 1);
    for (int i = 0; i < m_table_size; ++i)
    {
        User tmp;
        disk.Read(U_START + i * USR_SIZE, &tmp, USR_SIZE, 1);
        m_table[tmp.m_name] = std::make_shared<User>(tmp.m_name, tmp.m_password, tmp.m_index);
    }
}

bool UserManager::add(shared_ptr<User> ptr)
{
    if (m_table[ptr->m_name] == nullptr)
    {
        m_table[ptr->m_name] = ptr;
        m_table_size++;
        return true;
    }
    return false;
}

bool UserManager::erase(shared_ptr<User> ptr)
{
    if (m_table[ptr->m_name] != nullptr)
    {
        m_table[ptr->m_name] = nullptr;
        m_table_size--;
        return true;
    }
    return false;
}

bool UserManager::authentication(shared_ptr<User>& ptr)
{
    if (m_table[ptr->m_name] != nullptr)
    {
        string name = m_table[ptr->m_name].get()->m_name;
        string password = m_table[ptr->m_name].get()->m_password;
        uint32_t index = m_table[ptr->m_name].get()->m_index;
        if (name == ptr->m_name && password == ptr->m_password)
        {
            ptr = m_table[ptr->m_name];  // 得到用户指针
            return true;
        }
        return false;
    }
    return false;
}

UserManager::~UserManager()
{
    disk.Write(U_END, &m_table_size, sizeof(uint32_t), 1);
    int i = 0;
    for (auto tmp : m_table)
    {
        if (tmp.second != nullptr)
        {
            disk.Write(U_START + i * USR_SIZE, tmp.second.get(), USR_SIZE, 1);
            ++i;
        }
    }
}