#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*

dup(fd)：复制一个文件描述符返回最小可用的描述符
dup2(fd,new_fd)：复制描述符给指定描述符，原子的：包含close和fcntl


sync，将数据放入写队列中
fsync，对指定描述符刷新，写操作完成后返回
fdatasync，类似fsync但只针对数据不针对文件属性的刷新

其中update的守护进程周期性的调用sync

fcntl函数有5种功能(先说3种)： 
1. 复制一个现有的描述符(cmd=F_DUPFD). 
2. 获得/设置文件描述符标记(cmd=F_GETFD或F_SETFD). 
3. 获得/设置文件状态标记(cmd=F_GETFL或F_SETFL). 

*/

void get_file_access(int fd);

void test()
{
    int fd1 = dup(1);     //等同于fcntl(1,F_DUPFD,0);
    int fd2 = dup2(2, 4); //等同于close(4); fcntl(2,F_DUPFD,4);
    printf("fd1:%d\nfd2:%d\n", fd1, fd2);
    close(fd1);
    close(fd2);

    int fd = open("file/1.txt", O_RDWR | O_APPEND);
    printf("\nfile/1.txt:\n");
    get_file_access(fd);
    int flag = O_RDWR; //去除O_APPEND
    if (fcntl(fd, F_SETFL, flag) < 0)
    {
        fprintf(stderr, "fcntl error\n");
        close(fd);
        return;
    }
    printf("modified:\n");
    get_file_access(fd);
    close(fd);
}

void get_file_access(int fd)
{
    if (fd == -1)
    {
        fprintf(stderr, "not found test.txt\n");
        return;
    }
    int flag = fcntl(fd, F_GETFL, 0);
    if (flag < 0)
    {
        fprintf(stderr, "fcntl error\n");
        return;
    }
    int access = flag & O_ACCMODE;
    switch (access)
    {
    case O_RDWR:
        printf("read write mode\n");
        break;
    case O_RDONLY:
        printf("read only mode\n");
        break;
    case O_WRONLY:
        printf("write only mode\n");
        break;
    default:
        fprintf(stderr, "unknown access mode\n");
        break;
    }
    if (flag & O_NONBLOCK)
        printf("non block access mode enable\n");
    if (flag & O_APPEND)
        printf("append mode enable\n");
    if (flag & O_SYNC)
        printf("sync writes enable\n");
}

int main()
{
    test();
    return 0;
}