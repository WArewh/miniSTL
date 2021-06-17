#ifndef LAB_FOLDER_H_
#define LAB_FOLDER_H_

#include <unordered_map>

#include "file.h"


using std::unordered_map;

class Folder : public File
{
public:
    Folder(string name, uint32_t index);
    Folder(const IndexNode& node);
    ~Folder();

public:
    bool addFile(string name, uint32_t index);
    bool deleteFile(string name);
    shared_ptr<File> getFile(string name) { return m_table[name]; }

public:
    unordered_map<string, shared_ptr<File>> m_table;  //存储文件指针
};

#endif