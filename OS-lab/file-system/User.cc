#include "User.h"

User::User(string name, string password) : m_index(-1)
{
    strncpy(m_name, name.c_str(), name.length());
    m_name[name.length()] = '\0';
    strncpy(m_password, password.c_str(), password.length());
    m_password[password.length()] = '\0';
}

User::User(string name, string password, uint32_t index) : m_index(index)
{
    strncpy(m_name, name.c_str(), name.length());
    m_name[name.length()] = '\0';
    strncpy(m_password, password.c_str(), password.length());
    m_password[password.length()] = '\0';
}

User::~User()
{
}
