#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>

void main () {
	int serverfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in seradd;
	seradd.sin_family = AF_INET;
	seradd.sin_port = 4000;
	seradd.sin_addr.s_addr = INADDR_ANY;

	while (1) {
		char buf[100];
		printf(">> ");
		gets(buf);

		sendto(serverfd, buf, 100, 0, (struct sockaddr*) &seradd, sizeof(seradd));

		struct sockaddr_in incoming;
		int len = sizeof(incoming);

		recvfrom(serverfd, buf, 100, 0, (struct sockaddr*) &incoming, &len);
		printf("Server: %s\n", buf);
	}
}