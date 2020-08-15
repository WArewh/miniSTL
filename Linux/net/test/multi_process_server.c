#include "../wrap.h"

const short SERVERPORT = 8000;
const char* SERVERIP = "127.0.0.1";
const int   MAXCOUNT = 128;

void echo(int fd) {
    char buffer[BUFSIZ];

    while (1) {
        ssize_t n = Read(fd, buffer, BUFSIZ);

        if (n <= 0) {

            close(fd);
            exit(1);
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

void CatchChild(int signum) {
    int pid, statue;
    while ((pid = waitpid(0, &statue, WNOHANG)) > 0) {
        printf("child:%d statue:%d\n", pid, statue);
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

    struct sigaction child_act;
    child_act.sa_handler = CatchChild;
    sigemptyset(&child_act.sa_mask);
    child_act.sa_flags = 0;

    if (sigaction(SIGCHLD, &child_act, NULL) != 0) {
        sys_err("sigaction error");
    }

    while (1) {
        client_fd = Accept(listen_fd, &client_addr, &client_addr_length);
        int pid = fork();
        if (pid < 0) {

            sys_err("fork error");

        } else if (pid == 0) {

            close(listen_fd);
            echo(client_fd);

        } else {

            close(client_fd);
        }
    }


    return 0;
}