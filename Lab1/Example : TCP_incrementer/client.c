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
	int sockaddr_len = sizeof(struct sockaddr_in);

	// create socket for client
	int clientfd = socket(AF_INET, SOCK_STREAM, 0);

	// check for error
	if (clientfd == -1) {
		printf("Couldn't create socket! Exited.\n");
		exit(0);
	} else {
		printf("Socket created successfully!\n");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = PORT;

	// connect to server
	int status = connect(clientfd, (struct sockaddr*) &serverAddress, sockaddr_len);

	// check for error
	if (status == -1) {
		printf("Couldn't connect! Exited.\n");
		exit(0);
	} else {
		printf("Connected to server successfully!\n\n");
	}

	char ch;
	printf("Please type a character to send: ");
	scanf("%c", &ch);

	write(clientfd, &ch, 1);
	read(clientfd, &ch, 1);
	printf("Response from the server: %c\n\n", ch);

	close(clientfd);
}