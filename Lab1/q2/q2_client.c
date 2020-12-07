// author : Paawan Kohli
// Reg No : 180905416

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 150
#define PORT 9876

void main() {
    // create TCP socket
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    // check for errors
    if (serverfd == -1) {
        printf("Socket creation error. Exiting.\n");
        exit(0);
    } else {
        printf("Socket created successfully. ");
        printf("Socket ID : %d\n", serverfd);
    }

    // declare and configure server address
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // try to connect to the server
    int status = connect(serverfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // check for errors
    if (status == -1) {
        printf("Connection error. Exiting\n");
        exit(0);
    } else {
        printf("Connection established!\n\n");
    }

    // declare buffer and response arrays
    char buff[MAXSIZE], response[MAXSIZE];

    while (1) {
        // take input
        printf("Enter text: ");
        scanf("%s", buff);

        // check for 'QUIT'
        if (strcmp(buff, "QUIT") == 0) {
            printf("\n\nDisconnected!\n\n");
            send(serverfd, buff, sizeof(buff), 0);
            close(serverfd);
            break;
        }

        // send data to server
        send(serverfd, buff, sizeof(buff), 0);

        // recieve response from server
        int n = recv(serverfd, response, sizeof(response), 0);
        response[n] = '\0';

        printf("Response from server: %s \n\n", response);
    }
}