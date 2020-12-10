// author : Paawan Kohli
// Reg No : 180905416

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 7745

// matrix 
char mat[100][100];

// variable to track number of rows in the matrix
int rows = 0;

// function to add a row to the matrix
void addRow(char msg[100]) {
	strcpy(mat[rows++], msg);
}

void main() {
	// configure server address
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr, sizeof(servaddr));
	int len = sizeof(cliaddr);

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// create UDP socket
	int serverfd = socket(AF_INET, SOCK_DGRAM, 0);

	// check for error
	if (serverfd == -1) {
		printf("Couldn't create socket. Exiting!\n");
		exit(0);
	} else {
		printf("Socket created \n");
	}

	// bind the server fd to the socket
	int status = bind(serverfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	// check for error
	if (status == -1) {
		printf("Couldn't bind to socket. Exiting!\n");
		exit(0);
	} else {
		printf("Binding succesful \n\n");
	}

	while (1) {
		// create a buffer to recieve input from client
		char buffer[100];
		int n = recvfrom(serverfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
		buffer[n] = '\0';

		if (strcmp(buffer, "stop") == 0) {

			// close the socket
			printf("Client disconnected!\n\n");
			close(serverfd);
			break;

		} else {

			// add row
			addRow(buffer);

			// display matrix
			printf("Matrix is : \n");

			for (int k = 0; k < rows; k++)
				printf("%s \n", mat[k]);

			printf("\n");
		}
	}
}