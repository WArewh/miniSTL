#include <sys/epoll.h>

#include "../wrap.h"

const short SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
const int   MAXCOUNT = 128;

void echo(int tree_fd, struct epoll_event* e) {
    char buffer[5];
    int  fd = e->data.fd;
    while (1) {
        ssize_t n = Read(fd, buffer, 5);
        printf("errno=%d n=%ld\n", errno, n);
        if (n == -1 && errno == EAGAIN) {  //读完一次数据
            return;
        } else if (n <= 0) {  //结束或者出错
            epoll_ctl(tree_fd, EPOLL_CTL_DEL, fd, NULL);
            close(fd);
            return;
        }
        Write(fd, buffer, n);
        Write(STDOUT_FILENO, buffer, n);
    }
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
 * epoll
 * 使用红黑树完成监听
 * 触发方式:边缘触发(在添加数据的那一刻触发，因此需要while将所有数据读出)
 * 边缘触发会出现饥饿的情况(一个端口不断发送数据)
 *
 * 实际上写事件要在读事件后加入监听，这里由于输出在终端上因此省略
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
                // temp.events = EPOLLIN;
                temp.events = EPOLLIN | EPOLLET;
                temp.data.fd = client_fd;

                int flag = fcntl(client_fd, F_GETFL);
                flag |= O_NONBLOCK;
                fcntl(client_fd, F_SETFL, flag);

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