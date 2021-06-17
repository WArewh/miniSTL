#include "file.h"

File::File(string name, uint32_t index) : m_node(name, index)
{
}

File::File(const IndexNode& node) : m_node(node)
{
}

File::File(string name) : m_node(name, -1)
{
}

File::~File()
{
}