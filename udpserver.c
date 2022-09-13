
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
int myFunction(int x){
	if(x == 1)
		return 1;
	else
		return x*myFunction(x-1);
}
int main(){
    struct sockaddr_in client;
    int s,n;

    s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in server = {AF_INET,htons(8080),INADDR_ANY};

    bind(s,(struct sockaddr *)&server,sizeof(server));
    
    n=sizeof(client);
    int fact=1,num;
    while(num != -1){
	
    recvfrom(s,&num,sizeof(num),0,(struct sockaddr*)&client,&n);	
    if(num == -1){
	break;
	}
    fact = 1;
    fact = myFunction(num);
    sendto(s,&fact,sizeof(fact),0,(struct sockaddr*)&client,n);
    }
    fflush(stdout);
    close(s);	
   
    return 0;
}
