//Server program
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
	int sd,nd,n,len,reult;
	struct sockaddr_in seraddress, cliaddr;
	int buf[3],buf1[3];
	sd=socket(AF_INET, SOCK_STREAM,0);seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	bind(sd,(struct sockaddr*)&seraddress,sizeof(seraddress));
	listen(sd,5);
	len=sizeof(cliaddr);
	while(1)
	{
	nd=accept(sd,(struct sockaddr*)&cliaddr,&len);
	if (fork()==0){
	close(sd);
	n=read(nd,buf,sizeof(buf));
	switch(buf[2])
	{
		case '+':
		{
			buf1[0]=buf[0]+buf[1];
			break;
		}
		case '-':
		{
			buf1[0]=buf[0]-buf[1];
			break;
		}
		case '*':
		{
			buf1[0]=buf[0]*buf[1];
			break;
		}
		case '/':
		{
			buf1[0]=buf[0]/buf[1];
			break;
		}
	}
	n=write(nd,buf1,sizeof(buf1));
	getchar();
	close(nd);
	}
}
}