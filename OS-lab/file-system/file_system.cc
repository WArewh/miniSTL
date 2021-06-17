#include "file_system.h"


FileSystem::FileSystem(Disk& d, DataManager& dmanager, IndexManager& imanager,
                       UserManager& umanager)
    : disk(d),
      m_dmanager(dmanager),
      m_imanager(imanager),
      m_umanager(umanager),
      m_run(true),
      m_usr(nullptr)
{
    systemInit();
    commandMapInit();
}

void FileSystem::systemInit()
{
    disk.Read(S_START, &m_init, sizeof(bool), 1);
    if (m_init == false)
    {
        logonHelper("root", "root");
        m_init = true;
    }
}

void FileSystem::commandMapInit()
{
    m_command.insert("q");
    m_command.insert("login");
    m_command.insert("logout");
    m_command.insert("logon");
    m_command.insert("logoff");
    m_command.insert("cf");
    m_command.insert("df");
    m_command.insert("rf");
    m_command.insert("wf");
    m_command.insert("ls");

    m_map["q"] = &FileSystem::quit;
    m_map["login"] = &FileSystem::login;
    m_map["logout"] = &FileSystem::logout;
    m_map["logon"] = &FileSystem::logon;
    m_map["logoff"] = &FileSystem::logoff;
    m_map["ls"] = &FileSystem::listFiles;
    m_map["cf"] = &FileSystem::createFile;
    m_map["df"] = &FileSystem::deleteFile;
    m_map["rf"] = &FileSystem::readFile;
    m_map["wf"] = &FileSystem::writeFile;
}

void FileSystem::Run()
{
    while (m_run)
    {
        printHost();
        printUsr();
        string command;
        cin >> command;
        if (m_command.find(command) == m_command.end())
        {
            printf("指令错误!\n");
        }
        else
        {
            (this->*m_map[command])();
        }
    }
}
bool FileSystem::checkUser()
{
    if (m_usr == nullptr)
    {
        printf("请先登录!\n");
        return false;
    }
    return true;
}

void FileSystem::login()
{
    string name, password;
    printf("请输入用户名\n");
    cin >> name;
    printf("请输入密码\n");
    cin >> password;
    shared_ptr<User> tmp(new User(name, password));
    if (m_umanager.authentication(tmp))
    {
        uint32_t i_index = tmp->m_index;
        IndexNode inode;
        disk.Read(I_START + i_index * sizeof(IndexNode), &inode, sizeof(IndexNode), 1);
        shared_ptr<Folder> folder(new Folder(inode));
        m_usr = std::make_shared<UserInfo>(tmp, folder);
        printf("登录成功!\n");
    }
    else
    {
        printf("密码或用户名错误\n");
    }
}

void FileSystem::logout()
{
    if (m_usr == nullptr)
    {
        printf("请先登录\n");
    }
    else
    {
        m_usr = nullptr;
    }
}

void FileSystem::logon()
{
    string name, password;
    printf("请输入用户名\n");
    cin >> name;
    printf("请输入密码\n");
    cin >> password;
    if (logonHelper(name, password))
    {
        printf("用户注册完成!\n");
    }
    else
    {
        printf("已被注册过!注册失败!\n");
    }
}

bool FileSystem::logonHelper(string name, string password)
{
    shared_ptr<User> tmp(new User(name, password));
    if (m_umanager.add(tmp))
    {
        tmp->m_index = createDirHelper(name);
        return true;
    }
    return false;
}

void FileSystem::logoff()
{
    if (checkUser())
    {
        deleteDirHelper(m_usr->m_folder);
        m_umanager.erase(m_usr->m_data);
        m_usr = nullptr;
        printf("注销成功\n");
    }
    else
    {
        printf("请先登录\n");
    }
}

void FileSystem::createFile()
{
    if (checkUser())
    {
        string name;
        cin >> name;
        uint32_t index = m_imanager.getIndex();
        createFileHelper(name, index);
    }
}

bool FileSystem::createFileHelper(string name, uint32_t index)
{
    if (m_usr->m_folder->addFile(name, index))
    {
        auto ptr = m_usr->m_folder;
        writeFileHelper(ptr, -1, index);  //
        printf("文件创建成功!\n");
        return true;
    }
    else
    {
        printf("文件重名!\n");
        return false;
    }
}

bool FileSystem::writeFileHelper(shared_ptr<File> ptr, int start, uint32_t index)
{
    auto& inode = ptr->m_node;
    uint32_t length = sizeof(uint32_t);
    uint32_t i_index = inode.m_index;
    if (start == -1)
    {
        start = inode.m_size;
    }
    if (checkAndGetSpace(inode, start + length))
    {
        int b_index = start / BLOCK_SIZE;     //块下标
        int d_pos = inode.m_direct[b_index];  //在那个块
        int off = start % BLOCK_SIZE;         //偏移量
        DataBlock data_block;

        disk.Read(D_START + d_pos * BLOCK_SIZE, data_block.index(), BLOCK_SIZE, 1);
        data_block.m_index[off / 4] = index;
        disk.Write(D_START + d_pos * BLOCK_SIZE, data_block.index(), BLOCK_SIZE, 1);

        inode.m_size += length;
        disk.Write(I_START + i_index * sizeof(IndexNode), &inode, sizeof(IndexNode), 1);
        return true;
    }
    return false;
}

void FileSystem::readFile()
{
    if (checkUser())
    {
        printf("请输入文件名:\n");
        string name;
        cin >> name;
        auto ptr = m_usr->m_folder->getFile(name);
        if (ptr == nullptr)
        {
            printf("请先创建文件!\n");
        }
        else
        {
            uint32_t start, length;
            printf("请输入起点和长度\n");
            cin >> start >> length;
            if (readFileHelper(ptr, start, length))
            {
                printf("\n读取成功\n");
            }
            else
            {
                printf("读取失败\n");
            }
        }
    }
}

bool FileSystem::readFileHelper(shared_ptr<File> ptr, int start, uint32_t length)
{
    auto& inode = ptr->m_node;
    uint32_t i_index = inode.m_index;
    uint32_t f_size = inode.m_size;
    if (start + length <= f_size)
    {
        int b_index = start / BLOCK_SIZE;     //块下标
        int d_pos = inode.m_direct[b_index];  //在那个块
        int off = start % BLOCK_SIZE;         //偏移量

        DataBlock data_block;
        disk.Read(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);

        int total = length;

        while (1)
        {
            int cnt = BLOCK_SIZE - off;
            char buf[BLOCK_SIZE + 1];
            if (total > cnt)
            {
                strncpy(buf, data_block.data() + off, cnt);
                buf[cnt] = '\0';
                printf("%s", buf);
                total -= cnt;
                off = 0;
                d_pos = inode.m_direct[++b_index];
                disk.Read(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);
            }
            else
            {
                strncpy(buf, data_block.data() + off, total);
                buf[total] = '\0';
                printf("%s", buf);
                break;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

void FileSystem::writeFile()
{
    if (checkUser())
    {
        printf("请输入文件名:\n");
        string name;
        cin >> name;
        auto ptr = m_usr->m_folder->getFile(name);
        if (ptr == nullptr)
        {
            printf("请先创建文件!\n");
        }
        else
        {
            uint32_t start;
            string content;
            printf("请输入起点和内容\n");
            cin >> start >> content;
            if (writeFileHelper(ptr, start, content))
            {
                printf("写入成功\n");
            }
            else
            {
                printf("写入失败\n");
            }
        }
    }
}

bool FileSystem::writeFileHelper(shared_ptr<File> ptr, int start, string content)
{
    auto& inode = ptr->m_node;
    uint32_t length = content.length();
    uint32_t i_index = inode.m_index;
    if (start == -1)
    {
        start = inode.m_size;
    }
    if (checkAndGetSpace(inode, start + length))
    {
        int b_index = start / BLOCK_SIZE;     //块下标
        int d_pos = inode.m_direct[b_index];  //在那个块
        int off = start % BLOCK_SIZE;         //偏移量
        DataBlock data_block;

        disk.Read(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);

        int total = length;
        int pos = 0;
        while (1)
        {
            int cnt = BLOCK_SIZE - off;  // 剩余长度
            if (total > cnt)
            {
                strncpy(data_block.data() + off, content.c_str() + pos, cnt);
                total -= cnt;
                off = 0;
                pos += cnt;
                disk.Write(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);
                d_pos = inode.m_direct[++b_index];
                disk.Read(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);
            }
            else
            {
                strncpy(data_block.data() + off, content.c_str() + pos, total);
                disk.Write(D_START + d_pos * BLOCK_SIZE, &data_block, BLOCK_SIZE, 1);
                break;
            }
        }
        if (inode.m_size < start + length)
        {
            inode.m_size = start + length;
        }
        disk.Write(I_START + i_index * sizeof(IndexNode), &inode, sizeof(IndexNode), 1);
        return true;
    }
    else
    {
        return false;
    }
}


void FileSystem::deleteFile()
{
    if (checkUser())
    {
        string name;
        cin >> name;
        if (deleteFileHelper(name))
        {
            m_usr->m_folder->deleteFile(name);
            printf("文件删除成功!\n");
        }
        else
        {
            printf("文件未创建!\n");
        }
    }
}
bool FileSystem::deleteFileHelper(string name)
{
    auto file_ptr = m_usr->m_folder->getFile(name);
    if (file_ptr != nullptr)
    {
        //文件删除
        IndexNode& file_inode = file_ptr->m_node;
        uint32_t file_i_index = file_inode.m_index;
        for (int i = 0; i < 4; ++i)
        {  //释放数据块
            uint32_t d_index = file_inode.m_direct[i];
            if (d_index != -1)
            {
                m_dmanager.freeIndex(d_index);
            }
        }
        m_imanager.freeIndex(file_i_index);

        //文件夹里删除索引 将删除节点和最后一个节点交换，再进行删除
        auto& dir_inode = m_usr->m_folder->m_node;
        uint32_t d_index = 0;
        uint32_t d_pos = dir_inode.m_direct[d_index];

        DataBlock data_block[2];

        while (1)
        {
            disk.Read(D_START + d_pos * BLOCK_SIZE, &data_block[0], BLOCK_SIZE, 1);
            auto ptr1 = data_block[0].index(), ptr2 = data_block[1].index();
            int i = 0;
            for (i = 0; i < BLOCK_SIZE / sizeof(uint32_t); ++i)
            {
                if (ptr1[i] == file_i_index)
                {
                    break;
                }
            }
            if (i != BLOCK_SIZE / sizeof(uint32_t))
            {
                uint32_t end_d_index = dir_inode.m_size / BLOCK_SIZE;
                uint32_t end_d_pos = dir_inode.m_direct[end_d_index];
                uint32_t off = dir_inode.m_size % BLOCK_SIZE;
                if (off == 0)
                {
                    off = BLOCK_SIZE - sizeof(uint32_t);
                }
                else
                {
                    off -= sizeof(uint32_t);
                }
                off /= sizeof(uint32_t);
                if (end_d_pos == d_pos)
                {
                    ptr2 = data_block[0].index();
                    std::swap(ptr1[i], ptr2[off]);
                    disk.Write(D_START + end_d_pos * BLOCK_SIZE, &data_block[0], BLOCK_SIZE, 1);
                }
                else
                {
                    disk.Read(D_START + end_d_pos * BLOCK_SIZE, &data_block[1], BLOCK_SIZE, 1);
                    std::swap(ptr1[i], ptr2[off]);
                    disk.Write(D_START + d_pos * BLOCK_SIZE, &data_block[0], BLOCK_SIZE, 1);
                    disk.Write(D_START + end_d_pos * BLOCK_SIZE, &data_block[1], BLOCK_SIZE, 1);
                }
                break;
            }
            else
            {
                d_pos = dir_inode.m_direct[++d_index];
            }
        }
        dir_inode.m_size -= sizeof(uint32_t);
        // inode节点写回
        disk.Write(I_START + dir_inode.m_index * sizeof(IndexNode), &dir_inode, sizeof(IndexNode),
                   1);
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t FileSystem::createDirHelper(string name)
{
    uint32_t i_index = m_imanager.getIndex();
    shared_ptr<Folder> ptr(new Folder(name, i_index));
    disk.Write(I_START + i_index * sizeof(IndexNode), &ptr->m_node, sizeof(IndexNode), 1);
    return i_index;
}

bool FileSystem::deleteDirHelper(shared_ptr<Folder>& dir_ptr)
{
    if (dir_ptr != nullptr)
    {
        //删除内部文件
        for (auto file : dir_ptr->m_table)
        {
            if (file.second != nullptr)
            {
                deleteFileHelper(file.first);
            }
        }

        dir_ptr->m_table.clear();

        auto dir_inode = dir_ptr->m_node;

        for (int i = 0; i < 4; ++i)
        {  //释放数据块
            uint32_t d_pos = dir_inode.m_direct[i];
            if (d_pos != -1)
            {
                m_dmanager.freeIndex(d_pos);
            }
        }
        //释放索引节点
        m_imanager.freeIndex(dir_inode.m_index);
        return true;
    }
    else
    {
        return false;
    }
}

// 查询inode节点还有没有size大小空间，如果没有则申请空间
bool FileSystem::checkAndGetSpace(IndexNode& node, uint32_t size)
{
    if (size > node.m_capacity)
    {
        int cnt = (size - node.m_capacity) / BLOCK_SIZE + 1;

        int i = 0;
        for (i = 0; i < 4; ++i)
        {
            if (node.m_direct[i] == -1)
            {
                break;
            }
        }

        if (i + cnt > 4)
        {
            return false;
        }

        for (int j = i; j < i + cnt; ++j)
        {
            node.m_direct[j] = m_dmanager.getIndex();
        }

        node.m_capacity += cnt * BLOCK_SIZE;

        return true;
    }
    return true;
}

void FileSystem::listFiles()
{
    if (checkUser())
    {
        auto table = m_usr->m_folder->m_table;
        printf("Files:\n");
        printf("\t文件名  大小 inode data_block\n");
        for (auto tmp : table)
        {
            auto inode = tmp.second->m_node;
            printf("\t%-9s%-5d%-5d", inode.m_name, inode.m_size, inode.m_index);
            for (int i = 0; i < 4; ++i)
            {
                if (inode.m_direct[i] != -1)
                    printf("%-4d", inode.m_direct[i]);
            }
            printf("\n");
        }
    }
}

void FileSystem::quit()
{
    m_run = false;
}

void FileSystem::printUsr()
{
    if (m_usr != nullptr)
    {
        printf("%s:", m_usr.get()->m_data->m_name);
    }
    else
    {
        printf("null:");
    }
}

void FileSystem::printHost()
{
    printf("Ubuntu@");
}

FileSystem::~FileSystem()
{
    disk.Write(S_START, &m_init, sizeof(bool), 1);
}
