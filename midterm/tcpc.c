#include <sys/types.h>
#include <sys/socket.h> //
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h> //
#include <unistd.h>
#include <arpa/inet.h> //
#include <errno.h>

void main () {

	struct sockaddr_in seradd;
	int len = sizeof(seradd);

	seradd.sin_family = AF_INET;
	seradd.sin_port = 5555;
	seradd.sin_addr.s_addr = inet_addr("172.16.57.152");

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket fd: %d \n", fd);

	if (connect(fd, (struct sockaddr*)&seradd, len) == -1) {
		printf("Connect error! %d\n" , errno);
		exit(0);
	} else {
		printf("Connected\n");
	}

	char c = 'a';

	write(fd, &c, 1);

	char msg[100];

	read(fd, msg, 100);

	printf("Server: %s\n", msg);

}