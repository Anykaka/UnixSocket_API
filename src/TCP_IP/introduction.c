#include "introduction.h"

int GetClientTime(int argc, char **argv) {
    PRINTF printf("begain.\n");
    int socket_fd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        printf("input err.\n");
        return -1;
    }

    if (socket_fd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        printf("Socket err.\n");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        PRINTF printf("inet_pton err.\n");

    if (connect(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) <= 0)
        PRINTF printf("connect %d err.\n", socket_fd);
    
    while ((n = read(socket_fd, recvline, sizeof(recvline))) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            PRINTF printf("fputs err.\n");
    }

    if (n < 0) {
        PRINTF printf("read err.\n");
    }
    PRINTF printf("end.\n");
}