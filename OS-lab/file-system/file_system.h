#ifndef LAB_FILE_SYSTEM_H_
#define LAB_FILE_SYSTEM_H_

#include <iostream>
#include <unordered_map>

#include "User_manager.h"
#include "data_manager.h"
#include "disk.h"
#include "file.h"
#include "index_manager.h"

using std::cin;
using std::unordered_map;

const uint32_t S_START = 0;
const uint32_t S_SIZE = BLOCK_SIZE;
const uint32_t S_END = S_START + S_SIZE;

class FileSystem
{
public:
    FileSystem(Disk& disk, DataManager& dmanager, IndexManager& imanager, UserManager& umanager);
    ~FileSystem();

public:
    void Run();

private:
    void systemInit();
    void commandMapInit();
    void quit();
    void login();
    void logout();
    void logon();
    void logoff();
    void createFile();
    void readFile();
    void writeFile();
    void deleteFile();
    void listFiles();

private:
    void printUsr();
    void printHost();
    bool checkUser();
    bool checkAndGetSpace(IndexNode& node, uint32_t size);

private:
    bool logonHelper(string name, string password);
    bool createFileHelper(string name, uint32_t index);
    bool deleteFileHelper(string name);
    uint32_t createDirHelper(string name);
    bool deleteDirHelper(shared_ptr<Folder>& dir_ptr);
    bool writeFileHelper(shared_ptr<File> ptr, int start, string content);
    bool writeFileHelper(shared_ptr<File> ptr, int start, uint32_t index);
    bool readFileHelper(shared_ptr<File> ptr, int start, uint32_t length);

private:
    Disk& disk;
    DataManager& m_dmanager;
    IndexManager& m_imanager;
    UserManager& m_umanager;

private:
    using FS_FUNC = void (FileSystem::*)();
    unordered_map<string, FS_FUNC> m_map;
    unordered_set<string> m_command;

private:
    bool m_run;
    bool m_init;
    shared_ptr<UserInfo> m_usr;
};

#endif