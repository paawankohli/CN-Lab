// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	8080

int main() {

	// Create socket file descriptor
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// check for error
	if (sockfd < 0) {
		perror("Socket creation failed");
		exit(0);
	} else {
		printf("socket created successfully\n");
	}

	// configure server address
	struct sockaddr_in servaddr, cliaddr;
	int len = sizeof(cliaddr);

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("Server binding failed");
		exit(EXIT_FAILURE);
	} else {
		printf("Server binded successfully\n");
	}


	// exchange of message starts
	char RecvBuffer[1000];

	int n = recvfrom(sockfd, (char *)RecvBuffer, sizeof(RecvBuffer), 0,
	                 (struct sockaddr *) &cliaddr, &len);

	RecvBuffer[n] = '\0';

	printf("Client : "); puts(RecvBuffer);

	char *sendMsg = "Hey I'm the server. How many rows will you send?";

	sendto(sockfd, (char *)sendMsg, strlen(sendMsg), 0,
	       (struct sockaddr *) &cliaddr, len);

	int arrayBuffer[100];

	recvfrom(sockfd, (int *)arrayBuffer, sizeof(arrayBuffer), 0,
	         (struct sockaddr *) &cliaddr, &len);

	int rows = arrayBuffer[0];

	printf("Client : %d\n", rows);


	for (int r = 0 ; r < rows; r++) {
		printf("Array recieved: ");

		n = recvfrom(sockfd, (int *)arrayBuffer, sizeof(arrayBuffer), 0,
		             (struct sockaddr *) &cliaddr, &len);

		n = n / sizeof(int);

		for (int i = 0 ; i < n ; i++) {
			printf("%d ", arrayBuffer[i]);
		}

		printf("\n");
	}

	return 0;

}