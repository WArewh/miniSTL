#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <wait.h>
#include "myError.h"

//内存映射IO 共享内存

/* 
创建映射区需要读权限
offset需要是4096整数倍
map_private创建写时复制的区域 不会改变磁盘内容，因此不受文件的读写权限控制

*/

void test_mmap()
{
    int fd = open("test_mmap.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        sys_err("open error");
    }

    ftruncate(fd, 50);

    int length = lseek(fd, 0, SEEK_END);

    char *file_ptr = (char *)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    if (file_ptr == MAP_FAILED)
    {
        sys_err("mmap error");
    }

    strcpy(file_ptr, "mmap is a function\n");

    printf("%s", file_ptr);

    int ret = munmap(file_ptr, 50);
    if (ret == -1)
    {
        sys_err("munmap error");
    }
}

void fork_mmap()
{
    int fd = open("test_mmap.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        sys_err("open error");
    }

    ftruncate(fd, 4);

    int length = lseek(fd, 0, SEEK_END);

    int *ptr = (int *)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    close(fd);

    if (ptr == MAP_FAILED)
    {
        sys_err("mmap error");
    }

    *ptr = 0;
    pid_t pid = fork();

    if (pid < 0)
    {
        sys_err("fork error");
    }
    else if (pid == 0)
    {
        *ptr = 100;
        printf("address:%p\n", ptr);
        printf("child:%d\n", *ptr);
    }
    else
    {
        wait(NULL);
        printf("address:%p\n", ptr);
        printf("father:%d\n", *ptr);
    }
    // ptr的虚拟内存地址相同，存储内容不同，推测:父子进程映射关系不同
    int ret = munmap(ptr, 4);
    if (ret == -1)
    {
        sys_err("munmap error");
    }
}

void test_mmap_anon()
{
    int *ptr = (int *)mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED)
    {
        sys_err("mmap error");
    }

    *ptr = 0;
    pid_t pid = fork();

    if (pid < 0)
    {
        sys_err("fork error");
    }
    else if (pid == 0)
    {
        *ptr = 100;
        printf("address:%p\n", ptr);
        printf("child:%d\n", *ptr);
    }
    else
    {
        wait(NULL);
        printf("address:%p\n", ptr);
        printf("father:%d\n", *ptr);
    }
    // ptr的虚拟内存地址相同，存储内容不同，推测:父子进程映射关系不同
    int ret = munmap(ptr, 4);
    if (ret == -1)
    {
        sys_err("munmap error");
    }
}

int main()
{
    // test_mmap();
    // fork_mmap();
    test_mmap_anon();
    return 0;
}