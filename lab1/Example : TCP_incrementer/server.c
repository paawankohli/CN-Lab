#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 1327

void main () {
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	int sockaddr_len = sizeof(struct sockaddr_in);

	// create socket for server
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);

	// check for error
	if (serverfd == -1) {
		printf("Couldn't create socket! Exited.\n");
		exit(0);
	} else {
		printf("Socket created successfully!\n");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = PORT;

	// bind the socket and check for error
	int status = bind(serverfd, (struct sockaddr*) &serverAddress, sockaddr_len);

	if (status == -1) {
		printf("Couldn't bind socket! Exited.\n");
		exit(0);
	} else {
		printf("Socket binded successfully!\n");
	}

	// start listening with max backlog of 5
	status = listen(serverfd, 5);

	if (status == -1) {
		printf("Couldn't start listening! Exited.\n");
		exit(0);
	} else {
		printf("Server listening at port: PORT\n\n");
	}


	while (1) {
		printf("Server waiting for connection....\n");

		// accept incoming connection requests
		int clientfd = accept(serverfd, (struct sockaddr*) &clientAddress, &sockaddr_len);

		if (clientfd == -1) {
			printf("Couldn't accept connection request! Exited.\n");
			exit(0);
		} else {
			char *clientIP = inet_ntoa(clientAddress.sin_addr);
			int clientPort = clientAddress.sin_port;
			printf("Connection request accepted from ");
			printf("%s : %d\n", clientIP, clientPort);
		}

		char ch;

		read(clientfd, &ch, 1);
		ch++;
		write(clientfd, &ch, 1);

		close(clientfd);
		printf("Connection closed\n");
	}
}