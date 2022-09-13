#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80

void func(int sockfd);
int main(void)
{
	int port = 6001;
	char *ip = "127.0.0.1";

	//declare socket
	int server_id = socket(PF_INET,SOCK_STREAM,0);
	//define the socket
	struct sockaddr_in server;
	server.sin_family = PF_INET;
	server.sin_port = port;
	server.sin_addr.s_addr = inet_addr(ip);
	//try to establish communication
	int connection_status = connect(server_id,(struct
	sockaddr*)&server,sizeof(server));
	if(connection_status == -1)
	{
		printf("connection error");
		exit(9);
	}
	int num = 1;
	func(server_id);
	close(server_id);
	}
	void func(int sockfd)
	{
	char buff[MAX];
	int n;
	for (;;) {
	bzero(buff, sizeof(buff));
	printf("Enter the string : ");
	n = 0;
	while ((buff[n++] = getchar()) != '\n')
	;
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));
	printf("From Server : %s", buff);
	if ((strncmp(buff, "exit", 4)) == 0) 
	{
		printf("Client Exit...\n");
		break;
	}
	}
}
