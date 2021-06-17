#include "data.h"

DataBlock::DataBlock()
{
    memset(m_data, -1, sizeof(m_data));
}