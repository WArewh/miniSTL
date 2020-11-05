#include <pthread.h>

#include "../wrap.h"

const short SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
const int   MAXCOUNT = 128;


void* echo(void* arg) {
    char buffer[BUFSIZ];
    int  fd = *(int*)arg;
    while (1) {
        ssize_t n = Read(fd, buffer, BUFSIZ);

        if (n <= 0) {
            break;
        }

        Write(fd, buffer, n);
        Write(STDOUT_FILENO, buffer, n);
    }
    close(fd);
    return NULL;
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
    int client_fd;

    struct sockaddr_in server_addr;

    struct sockaddr_in client_addr;
    socklen_t          client_addr_length = sizeof(client_addr);

    SocketInit(&server_addr);

    Bind(listen_fd, &server_addr, sizeof(server_addr));

    Listen(listen_fd, MAXCOUNT);

    while (1) {
        client_fd = Accept(listen_fd, &client_addr, &client_addr_length);
        int       fd = client_fd;
        pthread_t t;
        pthread_create(&t, NULL, echo, (void*)&fd);
        pthread_detach(t);
    }


    return 0;
}