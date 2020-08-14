/* wrap.h */
#ifndef NET_WRAP_H
#define NET_WRAP_H

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void sys_err(const char* s);

int Accept(int fd, struct sockaddr_in* sa, socklen_t* salenptr);

void Bind(int fd, const struct sockaddr_in* sa, socklen_t salen);

void Connect(int fd, const struct sockaddr_in* sa, socklen_t salen);

void Listen(int fd, int backlog);

int Socket(int family, int type, int protocol);

ssize_t Read(int fd, void* ptr, size_t nbytes);

ssize_t Write(int fd, const void* ptr, size_t nbytes);

void Close(int fd);

ssize_t Readn(int fd, void* vptr, size_t n);

ssize_t Writen(int fd, const void* vptr, size_t n);

static ssize_t my_read(int fd, char* ptr);

ssize_t Readline(int fd, void* vptr, size_t maxlen);


#endif