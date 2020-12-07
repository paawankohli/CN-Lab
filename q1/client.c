// Client side implementation of UDP client-server model
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
	if (sockfd < 0 ) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	} else {
		printf("socket created successfully\n");
	}

	// configure server address
	struct sockaddr_in servaddr;
	int len = sizeof(servaddr);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;


	// exchange of message starts

	char *sendMsg = "Hey I'm the client.";

	sendto(sockfd, (char *)sendMsg, strlen(sendMsg), 0,
	       (struct sockaddr *) &servaddr, len);

	char RecvBuffer[100];

	int n = recvfrom(sockfd, (char *)RecvBuffer, sizeof(RecvBuffer), 0,
	                 (struct sockaddr *) &servaddr, &len);

	RecvBuffer[n] = '\0';
	printf("Server : "); puts(RecvBuffer);

	int **mat = malloc(3 * sizeof(int*));

	for (int i = 0 ; i < 3; i++) {
		mat[i] = malloc(4 * sizeof(int));

		printf("%d %d\n", sizeof(int), sizeof(mat[i]));

		mat[i][0] = (i + 1) * 10 + 1;
		mat[i][1] = (i + 1) * 10 + 2;
		mat[i][2] = (i + 1) * 10 + 3;
		mat[i][3] = (i + 1) * 10 + 4;
	}

	int rows = 3;
	// int rows = sizeof(mat) / sizeof(mat[0]);
	int rowarray[] = {rows};

	sendto(sockfd, rowarray, sizeof(rowarray), 0,
	       (struct sockaddr *) &servaddr, len);

	for (int i = 0 ; i < rows ; i++) {

		printf("%d\n", sizeof(mat[i]));

		sendto(sockfd, mat[i], sizeof(mat[i]), 0,
		       (struct sockaddr *) &servaddr, len);

		printf("%d row sent!\n", i);
	}


	return 0;
}