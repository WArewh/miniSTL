#ifndef LAB_FILE_H_
#define LAB_FILE_H_

#include <cstdint>
#include <cstring>
#include <functional>
#include <memory>
#include <vector>

#include "data.h"
#include "index_node.h"

using std::equal_to;
using std::hash;
using std::shared_ptr;
using std::vector;


const uint32_t F_MAX_SIZE = 4 * BLOCK_SIZE;

class File
{
public:
    File(string name, uint32_t index);
    File(const IndexNode& node);
    File(string name);
    virtual ~File();

public:
    IndexNode m_node;
};

#endif
