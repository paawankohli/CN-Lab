//TCP Client program:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
	int sd,nd,n,len,reult,n1;
	struct sockaddr_in seraddress, cliaddr;
	int buf[3],buf1[3];
	sd=socket(AF_INET, SOCK_STREAM,0);
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	len=sizeof(seraddress);
	connect(sd,(struct sockaddr*)&seraddress,len);
	printf("enter the number 1:\t");
	scanf("%d",&buf[0]);
	printf("enter the number 2:\t");
	scanf("%d",&buf[1]);
	printf("enter the operator:\t");
	scanf("%d",&buf[2]);
	n=write(sd,buf,sizeof(buf));
	n1=read(sd,buf1,sizeof(buf1));
	printf("answer from server %d\n",buf1[0]);
	getchar();
}