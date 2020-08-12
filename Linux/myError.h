#ifndef LINUX_ERROR_H_
#define LINUX_ERROR_H_

#include <stdio.h>
#include <stdlib.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

#endif