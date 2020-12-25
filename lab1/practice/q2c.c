#include <netinet/ip.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in seradd;
	int sockaddr_len = sizeof(seradd);

	seradd.sin_family = AF_INET;
	seradd.sin_port = 5000;
	seradd.sin_addr.s_addr = INADDR_ANY;

	connect(serverfd, (struct sockaddr*) &seradd, sockaddr_len);
	sleep(1000);
}