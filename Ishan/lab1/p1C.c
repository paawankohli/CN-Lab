//udp client driver program

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 5000
#define MAXLINE 1000

//driver code
int main()
{
	char buffer[100];
	int row[5];
	int sockfd, n, len;
	int size[1], i, j;
	struct sockaddr_in servaddr, cliaddr;

	//clear servaddr
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	//create datagram socket
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	printf("Enter Size of Matrix:\t");
	scanf("%d",&size[0]);
	sendto(sockfd,size,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	for ( i = 0; i < size[0]; i++)
	{
		printf("Enter row %d:\t", i+1);
		{
		for (j = 0; j < size[0]; j++)
			scanf("%d",&row[j]);
		sendto(sockfd,row,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		}
	}
	len = sizeof(cliaddr);

	//waiting for response
	n = recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
	buffer[n] = '\0';
	printf("message from ser is %s\n",buffer);
	getchar();

	//close the descriptor
	close(sockfd);
}