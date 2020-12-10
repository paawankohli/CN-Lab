// author : Paawan Kohli
// Reg No : 180905416

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6974

int evaluate(int x, int y, char op) {
    switch (op) {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '/':
        return x / y;
    case '*':
        return x * y;
    default:
        return 0;
    }
}

void main() {

    // create TCP socket
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

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int status = bind(serverfd, (struct sockaddr*)&server_address, sizeof(server_address));

    // check for error
    if (status == -1) {
        printf("Unable to bind. Exit.\n");
        exit(0);
    } else {
        printf("Binding successful.\n");
    }

    // listen
    status = listen(serverfd, 2);

    // check for error
    if (status == -1) {
        printf("Unable to listen. Exit.\n");
        exit(0);
    } else {
        printf("Server listening.\n\n");
    }


    // main logic:
    struct sockaddr_in client_address;
    int len = sizeof(client_address);

    while (1) {
        int clientfd = accept(serverfd, (struct sockaddr*)&client_address, &len);

        int x, y, status;
        char op;

        if (fork() == 0) {
            // child process logic:
            printf("Child process created. Clientfd: %d\n", clientfd);
            close(serverfd);

            // read input from client
            read(clientfd, (int*)&x, sizeof(int));
            read(clientfd, (int*)&y, sizeof(int));
            read(clientfd, (char*)&op, sizeof(char));

            int ans = evaluate(x, y, op);

            // send answer back to client
            write(clientfd, (int*)&ans, sizeof(int));
            close(clientfd);
            printf("Child process terminated. Clientfd: %d\n", clientfd);

            exit(0);
        } else {
            // parent process logic:
            close(clientfd);
        }

    }

    // close
    close(serverfd);
    printf("Disconnected!\n\n");
}