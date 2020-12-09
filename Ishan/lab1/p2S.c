//TCP Server program

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

//Function designed for chat between client and server
void servfunc(int sockfd, struct sockaddr_in cli)
{
	char buff[MAX];
	int n;
	//infinite loop for chat
	for (;;)
	{
		bzero(buff,MAX);

		//read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));

		//print buffer which contains the client contents
		printf("From client: %s", buff);
	    printf("Ephemeral Port Number %d\n", ntohs(cli.sin_port));
	    printf("Client IP address Number %s\n", inet_ntoa(cli.sin_addr));	    

		//Read server message from keyboard in the buffer
		for (n = 0; buff[n] != '\n'; n++)
			buff[n] = toupper(buff[n]);
		//and send that buffer to client
		write(sockfd,buff,sizeof(buff));

		//if message is exit, then server exit and session ended
		if (strncmp("QUIT",buff,4) == 0)
		{
			printf("Server Exit \n");
			break;
		}
	}
}

//Driver function
int main()
{
	int sockfd,connfd,len;
	struct sockaddr_in servaddr,cli;

	//socket create and verification
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		printf("socket creation failed \n");
		exit(0);
	}
	else
		printf("Socket successfully created \n");
	bzero(&servaddr,sizeof(servaddr));

	//assign IP,PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	//Binding newly created socket to given IP and verificiation
	if ((bind(sockfd,(SA*)&servaddr,sizeof(servaddr))) != 0)
	{
		printf("socket bind failed\n");
		exit(0);
	}
	else
		printf("Socket successfully binded\n");

	//Now server is ready to listen and verification
	if ((listen(sockfd,5)) != 0)
	{
		printf("Listen failed\n");
		exit(0);
	}
	else
		printf("Server listening\n");
	len = sizeof(cli);

	//Accept the data packet from client and verification
	connfd = accept(sockfd,(SA*)&cli, &len);
	if (connfd < 0)
	{
		printf("server accept failed\n");
		exit(0);
	}
	else
		printf("Server accepted client\n");

	//function for chatting between client and server
	servfunc(connfd,cli);

	//After sending exit message close the socket
	close(sockfd);
}