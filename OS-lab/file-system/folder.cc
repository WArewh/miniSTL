#include "folder.h"

Folder::Folder(string name, uint32_t index) : File(name, index)
{
}

Folder::Folder(const IndexNode& node) : File(node)
{
    uint32_t size = node.m_size;
    uint32_t i_index = 0;
    uint32_t d_index = node.m_direct[i_index];
    uint32_t pos = 0;
    DataBlock data_block;

    disk.Read(D_START + d_index * BLOCK_SIZE, data_block.index(), BLOCK_SIZE, 1);

    for (int i = 0; i < size / sizeof(uint32_t); ++i)
    {
        if (pos == BLOCK_SIZE / sizeof(uint32_t))
        {
            pos = 0;
            i_index++;
            d_index = node.m_direct[i_index];
            disk.Read(D_START + d_index * BLOCK_SIZE, data_block.index(), sizeof(uint32_t),
                      BLOCK_SIZE / sizeof(uint32_t));
        }
        uint32_t i_index = data_block.m_index[pos];
        IndexNode inode;
        disk.Read(I_START + i_index * sizeof(IndexNode), &inode, sizeof(IndexNode), 1);
        string name = inode.m_name;
        m_table[name] = shared_ptr<File>(new File(inode));
        ++pos;
    }
}

bool Folder::addFile(string name, uint32_t index)
{
    if (m_table[name] == nullptr)
    {
        m_table[name] = shared_ptr<File>(new File(name, index));
        auto& inode = m_table[name]->m_node;
        disk.Write(I_START + index * sizeof(IndexNode), &inode, sizeof(IndexNode), 1);
        return true;
    }
    return false;
}

bool Folder::deleteFile(string name)
{
    if (m_table[name] != nullptr)
    {
        m_table.erase(name);
        return true;
    }
    return false;
}

Folder::~Folder()
{
}