#include "../wrap.h"
#include "sys/select.h"

/*
 * 多路IO转接借助内核监听
 * 内部使用轮询且不能大于最大文件描述符(1023)
 * 可能出现max_fd很大，但是只有几个连接的情况，导致效率很低
 *
 */

const short SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";

void echo(int fd, fd_set* set) {
    char    buffer[BUFSIZ];
    ssize_t n = Read(fd, buffer, BUFSIZ);
    if (n <= 0) {
        close(fd);
        FD_CLR(fd, set);
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

int main() {

    int listen_fd = Socket(AF_INET, SOCK_STREAM, 0);
    int client_fd, max_fd = listen_fd;

    struct sockaddr_in server_addr;

    struct sockaddr_in client_addr;
    socklen_t          client_addr_length;

    fd_set read_set, reset_set;

    SocketInit(&server_addr);

    Bind(listen_fd, &server_addr, sizeof(server_addr));

    Listen(listen_fd, 128);

    FD_ZERO(&reset_set);
    FD_SET(listen_fd, &reset_set);

    while (1) {
        read_set = reset_set;
        int ret = select(max_fd + 1, &read_set, NULL, NULL, NULL);
        if (ret < 0) {
            sys_err("select error");
        }
        if (ret > 0) {
            if (FD_ISSET(listen_fd, &read_set)) {

                client_addr_length = sizeof(client_addr);
                client_fd = Accept(listen_fd, &client_addr, &client_addr_length);
                FD_SET(client_fd, &reset_set);
                if (max_fd < client_fd) {
                    max_fd = client_fd;
                }
                if (ret == 1) {  //只有listen_fd
                    continue;
                }
            }
            for (int i = listen_fd + 1; i <= max_fd; ++i) {

                int fd = i;
                if (FD_ISSET(fd, &read_set)) {
                    echo(fd, &reset_set);
                }
            }
        }
    }
    close(listen_fd);
    return 0;
}