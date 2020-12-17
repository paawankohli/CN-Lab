// author : Paawan Kohli
// Reg No : 180905416

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 9734

void main() {
    // create a TCP socket
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    // check for error
    if (serverfd == -1) {
        printf("Couldn't create socket. Exiting!\n");
        exit(0);
    } else {
        printf("Socket created \n");
    }

    // configure server address
    struct sockaddr_in server_address;
    int len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = PORT;

    // connect to server
    int status = connect(serverfd, (struct sockaddr *)&server_address, len);
    
    // check for error
    if (status == -1) {
        printf("Couldn't connect. Exiting!\n");
        exit(0);
    } else {
        printf("Connection established!\n\n");
    }

    char time[100];

    read(serverfd, time, 100);
    printf("Server Time: %s\n", time);

    char processid[100];

    read(serverfd, processid, 100);
    printf("Server proccess ID: %s\n", processid);

    // close
    close(serverfd);
}