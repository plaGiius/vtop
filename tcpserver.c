#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 80
void func(int name)
{
char buff[MAX];
int n;
// infinite loop for chat
for (;;) {
bzero(buff, MAX);
// read the message from client and copy it in buffer
read(name, buff, sizeof(buff));
// print buffer which contains the client contents
printf("From client: %sTo client : ", buff);
bzero(buff, MAX);
n = 0;
// copy server message in the buffer
while ((buff[n++] = getchar()) != '\n')
;
// and send that buffer to client
write(name, buff, sizeof(buff));
// if msg contains "Exit" then server exit and chat ended.
if (strncmp("exit", buff, 4) == 0) {
printf("Server Exit...\n");
break;
}
}
}
int main(void)
{
int port = 6001;
char *ip = "127.0.0.1";
//define socket
struct sockaddr_in server,client;
int server_id = socket(PF_INET,SOCK_STREAM,0);
server.sin_family = PF_INET;
server.sin_port = port;
server.sin_addr.s_addr = inet_addr(ip);
//bind it
int bindstatus = bind(server_id,(struct
sockaddr*)&server,sizeof(server));
//listen for communicaton
int listenstat = listen(server_id,5);
//accept requests
socklen_t addrlen = sizeof(client);

int newid = accept(server_id,(struct sockaddr*)&client,&addrlen);
if(newid != -1)
{
fflush(stdout);
printf("accepted\n");
}
int num = 1;
//chat
func(newid);
printf("connection terminated\n");
close(newid);
}
