#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include "myError.h"

void test_pipe()
{
    int fd[2];
    char *str = "hello!\n";
    char buf[1024];
    int ret = pipe(fd);
    if (ret == -1)
    {
        sys_err("pipe error");
    }
    int pid = fork();
    if (pid > 0)
    {
        close(fd[0]);
        sleep(1);
        write(fd[1], str, strlen(str));
        close(fd[1]);
    }
    else if (pid == 0)
    {
        close(fd[1]);
        ret = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        close(fd[0]);
    }
    else
    {
        sys_err("fork error");
    }
}

//ls | wc -l
void test2()
{
    int fd[2];
    int ret;
    pid_t pid;
    ret = pipe(fd);
    if (ret == -1)
    {
        sys_err("pipe error");
    }
    pid = fork();
    if (pid < 0)
    {
        sys_err("fork error");
    }
    else if (pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        wait(NULL);
        execlp("wc", "wc", "-l", NULL);
        sys_err("execlp wc error");
    }
    else
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        sys_err("execlp ls error");
    }
}

void test3()
{
    int fd[2];
    int ret;
    pid_t pid;
    ret = pipe(fd);
    if (ret == -1)
    {
        sys_err("pipe error");
    }
    int i;
    for (i = 0; i < 3; ++i)
    {
        int pid = fork();
        if (pid < 0)
        {
            sys_err("fork error");
        }
        else if (pid == 0)
        {
            break;
        }
    }
    switch (i)
    {
    case 0:
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        sys_err("execlp ls error");
        break;
    case 1:
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        sys_err("execlp wc error");
        break;
    case 2:

        break;
    case 3: //单向流动!
        // close(fd[0]);
        close(fd[1]);
        for (int i = 0; i < 3; ++i)
            wait(NULL);
    }
}

int main()
{
    // test_pipe();
    // test2();
    test3();
    return 0;
}