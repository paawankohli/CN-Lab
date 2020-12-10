//server program for UDP connection

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5000
#define MAXLINE 1000

//Server code
int main()
{
	int row[100];
	int servsockfd,len,n;
	int size[1], i, j;
	int matrix[100][100];
	struct sockaddr_in servaddr, cliaddr;
	bzero(&servaddr,sizeof(servaddr));

	//Create a UDP socket
	servsockfd = socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	//bind server address to socket descriptor
	bind(servsockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	//recieve the datagram
	len = sizeof(cliaddr);
	n = recvfrom(servsockfd, size, sizeof(size),0,(struct sockaddr*)&cliaddr,&len);
	printf("Size of matrix is %d\n", size[0]);
	for (i = 0; i < size[0]; i++)
	{
		n = recvfrom(servsockfd, row, sizeof(row),0,(struct sockaddr*)&cliaddr,&len);
		for (j = 0; j < size[0]; j++)
			matrix[i][j] = row[j];
	}
	for (i = 0; i < size[0]; i++)
	{
		for (j = 0; j < size[0]; j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}

	//Echoing back to the sclient
	sendto(servsockfd,"Matrix created succesfully",26,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	getchar();
	
	//close the descriptor
	close(servsockfd);
}