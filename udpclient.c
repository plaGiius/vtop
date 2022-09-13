
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    struct sockaddr_in client;
    int s,n,fact;

    s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in server={AF_INET,htons(8080),INADDR_ANY};

    n=sizeof(server);
	int num = 1;
	while(num != -1){

    printf("\nEnter number:");
    scanf("%d",&num);
	if(num == -1)
		break;
    sendto(s,&num,sizeof(num),0,(struct sockaddr*)&server,n);
    recvfrom(s,&fact,sizeof(fact),0,NULL,NULL);
    printf("Factorial: %d \n",fact);
}
    return 0;
}
