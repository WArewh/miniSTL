#include "index_node.h"


IndexNode::IndexNode(string name, uint32_t index) : m_index(index), m_size(0), m_capacity(0)
{
    strncpy(m_name, name.c_str(), name.length());
    m_name[name.length()] = '\0';
    for (int i = 0; i < 4; ++i)
    {
        m_direct[i] = -1;
    }
}

IndexNode::IndexNode(const IndexNode& node)
    : m_size(node.m_size),
      m_capacity(node.m_capacity),
      m_index(node.m_index)
{
    for (int i = 0; i < 4; ++i)
    {
        m_direct[i] = node.m_direct[i];
    }
    strncpy(m_name, node.m_name, strlen(node.m_name));
    m_name[strlen(node.m_name)] = '\0';
}

IndexNode::~IndexNode()
{
}