#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <sys/stat.h>
#include "myError.h"

//命名管道 创建后的操作和文件相同

void test_fifo()
{
    char *path = "myfifo";
    int ret = mkfifo(path, 0644);
    if (ret == -1)
    {
        sys_err("mkfifo error");
    }
}

int main()
{
    test_fifo();
    return 0;
}