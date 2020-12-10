// author : Paawan Kohli
// Reg No : 180905416

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

    // declare client and server address
    struct sockaddr_in serveraddr, clientaddr;
    int len = sizeof(clientaddr);

    // configure server address
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

    // bind serverfd to socket
    int status = bind(serverfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // check for errors
    if (status == -1) {
        printf("Binding failed. Exiting.\n");
        exit(0);
    } else {
        printf("Binded successfully.\n");
    }

    // start listening
    status = listen(serverfd, 5);

    // check for errors
    if (status == -1) {
        printf("Listening failed. Exiting.\n");
        exit(0);
    } else {
        printf("Server is listening.\n\n");
    }

    // accept connection request
    int clientfd = accept(serverfd, (struct sockaddr*)&clientaddr, &len);

    char buff[MAXSIZE];

    while (1) {
        // recieve data from client
        recv(clientfd, buff, sizeof(buff), 0);

        // check for 'QUIT'
        if (strcmp(buff, "QUIT") == 0) {
            printf("\n\nDisconnected!\n\n");
            close(serverfd);
            close(clientfd);
            break;
        } else {
            // print details of client
            printf("IP: %s\n", inet_ntoa(clientaddr.sin_addr));
            printf("Port: %d\n", ntohs(clientaddr.sin_port));
            printf("String sent by client: %s \n\n", buff);
            
            // convert string
            for (int i = 0; i < strlen(buff); i++)
                buff[i] = toupper(buff[i]);
        
            // send back the converted
            send(clientfd, buff, sizeof(buff), 0);
        }
    }
}