// author : Paawan Kohli
// Reg No : 180905416

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PORT 7745

void main() {
	// configure server address
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	// make a UDP socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	while (1) {
		char buffer[100];
		printf("Enter array or enter 'stop': \n");
		gets(buffer);
		printf("\n");

		// sending data starts
		if (strcmp(buffer, "stop") == 0) {
			printf("\nClosing connection\n");
			sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
			close(sockfd);
			break;
		}
		else {
			sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
		}
	}
}