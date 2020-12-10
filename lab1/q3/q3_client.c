// author : Paawan Kohli
// Reg No : 180905416

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 6974

void main() {
    // create x TCP socket
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    // check for error
    if (serverfd == -1) {
        printf("Couldn't create socket. Exit.\n");
        exit(0);
    } else {
        printf("Socket created successfully!\n");
    }

    // configure server address
    struct sockaddr_in server_address;
    int len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);

    // try to connect to server
    int status = connect(serverfd, (struct sockaddr*)&server_address, len);

    // check for errors
    if (status == -1) {
        printf("Can't establish connection. Exit.\n");
        exit(0);
    } else {
        printf("Connection established\n\n");
    }

    // main logic:
    printf("Enter expression: ");

    int x, y;
    char op;

    scanf("%d %c %d", &x, &op, &y);

    write(serverfd, (int*)&x, sizeof(int));
    write(serverfd, (int*)&y, sizeof(int));
    write(serverfd, (char*)&op, sizeof(char));

    int ans;
    read(serverfd, (int*)&ans, sizeof(int));

    printf("Answer: %d\n\n", ans);

    // close
    close(serverfd);
    printf("Disconnected!\n\n");
}