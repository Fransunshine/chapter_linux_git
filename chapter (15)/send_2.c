#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
int sendn(int sfd, char*buf, int len)
{
	int send_sum = 0 ;
	int send_ret ;

	while(send_sum < len)
	{
		send_ret = send(sfd, (char*)buf + send_sum, len - send_sum, 0);

		
		send_sum += send_ret ;

	}
	return send_sum;
}
int main(int argc, char* argv[])//ip  port
{
	int sfd ;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in seraddr ;

	memset(&seraddr, 0, sizeof(seraddr));

	seraddr.sin_family = AF_INET ;

	seraddr.sin_port = htons(atoi(argv[2]));

	seraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == connect(sfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) )
	{
		perror("bind");
		close(sfd);
		exit(1);
	}
	int len ;
	char buf[1024] ;
/*
	if(fork() == 0)
	{
		while(1) ;
		exit(1);
	}*/
	//shutdown(sfd, SHUT_WR);
	//shutdown(sfd, SHUT_RD);
	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
	{
		len = strlen(buf);
		send(sfd, &len, 4, 0);

		sendn(sfd, buf, len);

	}
	len = 0 ;
	send(sfd, &len, 4, 0);
	printf("over!\n");
//	close(sfd);
	shutdown(sfd, SHUT_RDWR);

	return 0 ;
}
