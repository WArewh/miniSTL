#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include "myError.h"

const size_t total = 5;
size_t count = 0;

void handler_sigchld(int sig)
{
    pid_t pid;
    int statue;
    while ((pid = waitpid(-1, &statue, 0)) > 0)
    {
        if (WIFEXITED(statue))
        {
            printf("sigchld:%d statue:%d\n", pid, WIFEXITED(statue));
            ++count;
        }
    }
    return;
}

int main()
{
    pid_t pid;
    int i;

    sigset_t new_set, old_set;
    sigemptyset(&new_set);
    sigfillset(&new_set);

    sigprocmask(SIG_BLOCK, &new_set, &old_set);

    for (i = 0; i < total; ++i)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
        else if (pid == -1)
        {
            sys_err("fork error");
        }
    }
    if (i == total)
    {
        struct sigaction action;
        action.sa_handler = handler_sigchld;
        action.sa_flags = 0;
        sigemptyset(&action.sa_mask);

        int ret = sigaction(SIGCHLD, &action, NULL);
        if (ret == -1)
        {
            sys_err("sigaction error");
        }

        printf("parent:%d\n", getpid());

        sigprocmask(SIG_SETMASK, &old_set, NULL);

        // printf("parent:%d\n", getpid());

        while (count != total)
            ;
    }
    else
    {
        printf("child:%d\n", getpid());
        return i;
    }

    return 0;
}