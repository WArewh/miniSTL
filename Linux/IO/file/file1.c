#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "error.h"

/*
文件IO

不带缓冲的I/O，他们都是执行一个系统调用

open
openat
crate
close
lseek
read
write

文件描述符(非负数)，打开一个文件就对应一个描述符
其中0为标准输入、1为标准输出、2为标准错误

openat和open的区别在于openat多了一个dir_fd(见底下的use3函数)

lseek的偏移量可以大于文件长度，多出来的部分会补0,但暂时不会占用磁盘空间，且不进行任何IO操作

多数文件系统采用预读的技术，会试图要求更多数据，假想不久的将来会使用到他们

*/

char buffer[1024];

void use1()
{
    int fd = open("file/1.txt", O_RDONLY);
    int length = 0;
    if (fd == -1)
    {
        fprintf(stderr, "not found 1.txt\n");
        return;
    }

    while ((length = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        *(buffer + length + 1) = '\0';
        printf("%s\n", buffer);
    }

    close(fd);
}

void use2()
{
    char *file_path = "file/2.txt";
    int fd = creat(file_path, 0644);
    //等同于open(file_path, O_WRONLY | O_TRUNC | O_CREAT,0644);
    if (fd == -1)
    {
        fprintf(stderr, "can't create 2.txt\n");
        return;
    }
    char *data = "ABCDEFGH";
    int length = strlen(data);
    int write_length = write(fd, data, length);
    if (write_length != length)
    {
        fprintf(stderr, "write error\n");
        return;
    }
    close(fd);
}

void use3()
{
    int dir_fd = open("./file", O_RDONLY);
    int length = 0;
    if (dir_fd == -1)
    {
        fprintf(stderr, "can't open .\n");
        return;
    }
    int fd = openat(dir_fd, "1.txt", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "can't open 1.txt\n");
        return;
    }
    if (lseek(fd, 3, SEEK_SET) == -1)
    {
        fprintf(stderr, "can't lseek\n");
        return;
    }
    while ((length = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        *(buffer + length + 1) = '\0';
        printf("%s\n", buffer);
    }
}

int main()
{
    // use1();
    use2();
    // use3();
    return 0;
}