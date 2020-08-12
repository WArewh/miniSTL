#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
/* 

fileno获取对应描述符文件

制造临时文件
tempnam
tmpfile 临时二进制

mkdtemp临时创建一个目录
mkstemp临时创建一个文件

*/
void test_temp()
{
    char file_name[L_tmpnam];
    FILE *fp;
    int fd;
    printf("%s\n", tempnam(".", NULL)); //不建议使用
    fp = tmpfile();
    fd = fileno(fp);
    printf("%d\n", fd);

    char tmp_dir_name[] = "std/dir_XXXXXX"; //不能用指针 因为指向字符串会放在常量区
    char tmp_file_name[] = "std/file_XXXXXX";
    char *tmp_name;
    if ((fd = mkstemp(tmp_file_name)) < 0)
    {
        fprintf(stderr, "can't create temp dir\n");
        return;
    }
    if ((tmp_name = mkdtemp(tmp_dir_name)) == NULL)
    {
        fprintf(stderr, "can't create temp dir\n");
        return;
    }
    printf("%s\n", tmp_name);
    // mkdtemp和mkstemp生成的文件不会自动消失
    unlink(tmp_dir_name);
    unlink(tmp_file_name);
}

/* 

内存流
直接向内存读写数据

fmeopen内存流创建
open_memstream　面向字节
open_wmenstream　面向宽字节

*/

void test_memory()
{
    FILE *fp;
    const int buffer_size = 40;
    char buffer[buffer_size];

    fp = fmemopen(buffer, buffer_size, "w");

    memset((void *)&buffer, 'a', buffer_size);
    buffer[buffer_size - 1] = 'X';
    buffer[buffer_size - 2] = '\0';
    fprintf(fp, "hello");
    printf("before fflush:\n");
    printf("%s\n", buffer);
    fflush(fp);
    printf("after fflush:\n");
    printf("%s\n", buffer);

    memset((void *)&buffer, 'b', buffer_size);
    buffer[buffer_size - 1] = 'X';
    buffer[buffer_size - 2] = '\0';
    fprintf(fp, "hello");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek:\n");
    printf("%s\n", buffer);

    memset((void *)&buffer, 'c', buffer_size);
    buffer[buffer_size - 1] = 'X';
    buffer[buffer_size - 2] = '\0';
    fprintf(fp, "hello");
    fclose(fp);
    printf("after fclose:\n");
    printf("%s\n", buffer);
}

int main()
{
    // test_temp();
    test_memory();
    return 0;
}