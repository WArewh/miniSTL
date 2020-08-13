#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "myError.h"

/*
 * 服务端
 * 创建套接字 socket
 * 绑定套接字 bind
 * 设置监听数 listern
 * 接受连接 accept
 * 处理连接 read write
 * 结束连接 close
 */

const int   SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
char        buffer[BUFSIZ];

int main() {
    int ret;

    int                listen_fd;
    struct sockaddr_in server_addr;

    int                client_fd;
    struct sockaddr_in client_addr;
    socklen_t          client_addr_length;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_fd == -1) {
        sys_err("socket error");
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, SERVERIP, &server_addr.sin_addr.s_addr);
    client_addr_length = sizeof(client_addr);

    ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (ret == -1) {
        close(listen_fd);
        sys_err("bind error");
    }

    ret = listen(listen_fd, 128);

    if (ret == -1) {
        sys_err("listen error");
    }

    client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_length);

    if (client_fd == -1) {
        sys_err("accept error");
    }

    char client_ip[BUFSIZ];
    printf("client ip:%s\nclient port%d\n",
           inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, BUFSIZ),
           ntohs(client_addr.sin_port));

    while (read(client_fd, buffer, BUFSIZ) > 0) {
        write(client_fd, buffer, BUFSIZ);
    }

    close(listen_fd);
    close(client_fd);
    return 0;
}