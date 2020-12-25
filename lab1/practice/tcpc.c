#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

void main () {

	struct sockaddr_in seradd;
	int sockaddr_len = sizeof(seradd);

	seradd.sin_family = AF_INET;
	seradd.sin_port = 1326;
	seradd.sin_addr.s_addr = inet_addr("127.0.0.1");

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	connect(fd, (struct sockaddr*)&seradd, sockaddr_len);

	while (1) {
		printf("enter n and elements: ");
		int n; scanf("%d", &n);
		
		int arr[n + 1];
		arr[0] = n;

		for (int i = 1; i <= n; ++i)
			scanf("%d", &arr[i]);

		write(fd, arr, (n + 1) * 4);

		if (n == 0) {
			break;
		}
	}


}