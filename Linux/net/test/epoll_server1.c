#include <sys/epoll.h>

#include "../wrap.h"

const short SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
const int   MAXCOUNT = 128;

void echo(int tree_fd, struct epoll_event* e) {
    char    buffer[BUFSIZ];
    int     fd = e->data.fd;
    ssize_t n = Read(fd, buffer, BUFSIZ);
    if (n <= 0) {
        epoll_ctl(tree_fd, EPOLL_CTL_DEL, fd, NULL);
        close(fd);
        return;
    }
    Write(fd, buffer, n);
    Write(STDOUT_FILENO, buffer, n);
}

void SocketInit(struct sockaddr_in* sock) {
    bzero(sock, sizeof(struct sockaddr_in));
    sock->sin_family = AF_INET;
    sock->sin_port = htons(SERVERPORT);
    if (inet_pton(AF_INET, SERVERIP, &sock->sin_addr.s_addr) < 0 || errno == EAFNOSUPPORT) {
        sys_err("inet_pton error");
    }
}


/*
 * poll原理基本同select,epoll的半成品
 * 使用结构体，可以将监听集合和返回事件集合分离
 * 拓展了监听上限
 * 不能跨平台
 * 无法直接定位出现事件的描述符(可优化)
 *
 * epoll
 * 使用红黑树完成监听
 * 触发方式:水平触发(有数据就触发)
 *
 */

int main() {

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    int client_fd, max_fd = listen_fd;

    struct sockaddr_in server_addr;

    struct sockaddr_in client_addr;
    socklen_t          client_addr_length;

    SocketInit(&server_addr);

    Bind(listen_fd, &server_addr, sizeof(server_addr));

    Listen(listen_fd, MAXCOUNT);

    int tree_fd = epoll_create(MAXCOUNT);

    if (tree_fd == -1) {
        sys_err("epoll_create error");
    }

    struct epoll_event e, events[MAXCOUNT];
    e.events = EPOLLIN;
    e.data.fd = listen_fd;

    int ret = epoll_ctl(tree_fd, EPOLL_CTL_ADD, listen_fd, &e);
    if (ret == -1) {
        sys_err("epoll_ctl error");
    }

    while (1) {
        int ready = epoll_wait(tree_fd, events, MAXCOUNT, -1);
        if (ready == -1) {
            sys_err("epoll_wait error");
        }
        for (int i = 0; i < ready; ++i) {
            if (!(events[i].events & EPOLLIN)) {  //不是读事件跳过
                continue;
            }
            if (events[i].data.fd == listen_fd) {

                client_addr_length = sizeof(client_addr);
                client_fd = Accept(listen_fd, &client_addr, &client_addr_length);

                struct epoll_event temp;
                temp.events = EPOLLIN;
                temp.data.fd = client_fd;

                ret = epoll_ctl(tree_fd, EPOLL_CTL_ADD, client_fd, &temp);
                if (ret == -1) {

                    sys_err("epoll_ctl error");
                }

            } else {
                echo(tree_fd, &events[i]);
            }
        }
    }
    return 0;
}