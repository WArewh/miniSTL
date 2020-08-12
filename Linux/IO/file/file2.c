#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* 

每个进程都有一张文件描述符表，不同文件打开同一文件，fd可能不同，
但v节点相同，这就达到文件共享的目的，但多个进程进行操作，可能会造成问题。

linux提供O_APPEND标志,它会让lseek和写变为一个原子操作 

pread和pwrite 原子操作
调用pread，无法中断定位和读操作，但不更新文件偏移指针
pwrite，和pread类似，同样不会更新文件偏移指针


*/

char buffer[4096];
char *file_path = "file/test.txt";

//文件共享
void test()
{
    int fd = open(file_path, O_WRONLY | O_APPEND | O_CREAT);
    int loop = 10;
    if (fd == -1)
    {
        fprintf(stderr, "not found test.txt\n");
        return;
    }
    int pid = fork();
    if (pid == -1)
    {
        fprintf(stderr, "can't create process\n");
        return;
    }
    if (pid == 0)
    {
        char *data = "BBBBBBBBBB";
        int length = strlen(data);
        for (int i = 0; i < loop; ++i)
        {
            int write_length = write(fd, data, length);
            if (write_length != length)
            {
                fprintf(stderr, "write error\n");
                return;
            }
        }
        close(fd);
        exit(0);
    }
    else
    {
        char *data = "AAAAAAAAAA";
        int length = strlen(data);
        for (int i = 0; i < loop; ++i)
        {
            int write_length = write(fd, data, length);
            if (write_length != length)
            {
                fprintf(stderr, "write error\n");
                return;
            }
        }
        close(fd);
    }
    wait(NULL);
    fsync(fd);
}

void test2()
{
    int fd = open(file_path, O_CREAT | O_RDWR);
    if (fd == -1)
    {
        fprintf(stderr, "not found test.txt\n");
        return;
    }
    char *data = "CCCCCCCCCC";
    int data_length = strlen(data);

    int length = 0, total_length = lseek(fd, 0, SEEK_END);
    if ((length = pwrite(fd, data, data_length, total_length)) != data_length)
    {
        fprintf(stderr, "write error\n");
        return;
    }

    length = 0, total_length = 0;
    //由于，不更新文件偏移量，因此需要自己设置一个偏移量
    while ((length = pread(fd, buffer, sizeof(buffer), total_length)) > 0)
    {
        total_length += length;
    }
    printf("result:%d\n", total_length);
    close(fd);
}

int main()
{
    test();
    test2();
    return 0;
}