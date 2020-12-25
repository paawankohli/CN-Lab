#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

void main () {

	struct sockaddr_in cliadd, seradd;
	int sockaddr_len = sizeof(seradd);

	seradd.sin_family = AF_INET;
	seradd.sin_port = 1326;
	seradd.sin_addr.s_addr = inet_addr("127.0.0.1");

	int serverfd = socket(AF_INET, SOCK_STREAM, 0);

	if (serverfd == -1) {
		printf("Can't create socket\n");
		exit(0);
	}

	if (bind(serverfd, (struct sockaddr*) &seradd, sockaddr_len) == -1) {
		printf("Can't bind\n");
		exit(0);
	}

	if (listen(serverfd, 10) == -1) {
		printf("Can't listen\n");
		exit(0);
	}

	printf("Waiting for connection!\n");

	int clientfd = accept(serverfd, (struct sockaddr*)&cliadd, &sockaddr_len);

	printf("Connection established!\n");
	printf("IP: %s\n", inet_ntoa(cliadd.sin_addr));
	printf("Port: %d\n", cliadd.sin_port);

	int mat[100][100];
	int i = 0;

	while (1) {
		int arr[100];
		read(clientfd, arr, 100 * 4) / 4;
		int size = arr[0];

		if (size == 0) {
			break;
		}

		for (int j = 0 ; j <= size ; j++) {
			mat[i][j] = arr[j];
		}

		i++;

		printf("Got line %d\n", 1);
	}

	for (int ii = 0 ; ii < i ; ii++) {
		int size = mat[ii][0];

		for (int j = 1 ; j <= size ; j++) {
			printf("%d ", mat[ii][j]);
		}

		printf("\n");
	}

	close(clientfd);
}