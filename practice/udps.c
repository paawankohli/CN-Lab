#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string.h>

void main () {
	int serverfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in seradd;
	seradd.sin_family = AF_INET;
	seradd.sin_port = 4000;
	seradd.sin_addr.s_addr = INADDR_ANY;

	bind(serverfd, (struct sockaddr *) &seradd, sizeof(seradd));

	while (1) {
		char buf[100];
		struct sockaddr_in cliadd;
		int len = sizeof(cliadd);

		recvfrom(serverfd, buf, 100, 0, (struct sockaddr*) &cliadd, &len);
		printf("Client: %s\n", buf);

		strcpy(buf, "Got it bro");

		sendto(serverfd, buf, 100, 0, (struct sockaddr*) &cliadd, len);
	}
}