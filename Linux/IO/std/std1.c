#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
/*

打开一个流
fopen
freopen(重定向输入输出流)
fdopen(常用于创建管道或网络通信返回的描述符)

关闭一个流
fclose

读写一个流
字符:fgetc fputc getchar putchar(错误或读尽返回EOF)
一行:fgets fputs
直接:fread fwrite

feof、ferror判断产生EOF的原因

clearerr清除出错和文件结束标志

定位一个流
ftell、ftello得到当前位置
fseek、fseeko类似lseek

fsetpos、fgetpos设置/得到位置


格式化IO略

*/

char *file_path1 = "std/1.txt";
char *file_path2 = "std/2.txt"; //测试重定向
char *file_data = "std/data";   //测试二进制
char buffer[2];
void test_write()
{
    FILE *fp = fopen(file_path1, "w"); //没有会创建文件
    if (fp == NULL)
    {
        fprintf(stderr, "not found 1.txt\n");
        return;
    }
    fputc('a', fp);
    fputs("bcd\nefgh\nijklmn\n", fp);
    fclose(fp);
}

void test_read()
{
    FILE *fp = fopen(file_path1, "r");
    int ch;
    if (fp == NULL)
    {
        fprintf(stderr, "not found 1.txt\n");
        return;
    }
    printf("%c\n", fgetc(fp));
    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer);
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar((char)ch);
    }
    if (feof(fp) == 1)
    {
        printf("read finish\n");
    }
    if (ferror(fp) == 1)
    {
        printf("read error\n");
    }
    fclose(fp);
}

void test_reopen()
{
    FILE *fp = freopen(file_path2, "w", stdout);
    if (fp == NULL)
    {
        fprintf(stderr, "can't freopen 2.txt\n");
        return;
    }
    for (int i = 0; i < 5; ++i)
    {
        printf("%-2d", i);
    }
    fp = freopen("/dev/tty", "w", stdout); //恢复
    for (int i = 0; i < 5; ++i)
    {
        printf("%-2d", i);
    }
    printf("\n");
    fclose(fp);
}

void test_binary()
{
    int write_array[4] = {1, 2, 3, 4};
    int read_array[3];
    FILE *fp = fopen(file_data, "w+");
    if (fp == NULL)
    {
        fprintf(stderr, "can't open data_file\n");
        return;
    }
    if (fwrite(&write_array[1], sizeof(int), 3, fp) != 3)
    {
        fprintf(stderr, "write error in data_file\n");
        return;
    }
    fseek(fp, 0, SEEK_SET); //定位
    if (fread(&read_array, sizeof(int), 3, fp) != 3)
    {
        fprintf(stderr, "read error in data_file\n");
        return;
    }
    for (int i = 0; i < 3; ++i)
    {
        printf("%-2d", read_array[i]);
    }
    printf("\n");
    fclose(fp);
}

void test()
{
    test_write();
    test_read();
    // test_reopen();
    // test_binary();
}

int main()
{
    test();
    return 0;
}