#include <netinet/ip.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in cliadd, seradd;
	int sockaddr_len = sizeof(cliadd);

	seradd.sin_family = AF_INET;
	seradd.sin_port = 5000;
	seradd.sin_addr.s_addr = INADDR_ANY;

	bind(serverfd, (struct sockaddr*) &seradd, sockaddr_len);
	listen(serverfd, 10);

	while (1) {
		int newfd = accept(serverfd, (struct sockaddr*) &cliadd, &sockaddr_len);

		if (fork() == 0) {
			printf("Connected to client from port %d\n", cliadd.sin_port);
			sleep(10000);
		} 
	}

}