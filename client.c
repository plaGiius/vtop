#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{ 
    char *ip = "127.0.0.1";
    int port = 5566;
    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;
    char str[20];
    int pnr;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){ 
        perror("[-]Socket error");
        exit(1);
    }
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    while(1){
            bzero(buffer, 1024); 
            recv(sock, buffer, sizeof(buffer), 0); // Boarding point 
            printf("%s\n", buffer); 
            
            bzero(buffer, 1024);
            scanf("%s", str);
            strcpy(buffer, str);  
            send(sock, buffer, strlen(buffer), 0); 
            
            bzero(buffer, 1024); 
            recv(sock, buffer, sizeof(buffer), 0); // Dropping Point 
            printf("%s\n", buffer); 
            
            bzero(buffer, 1024); 
            scanf("%s", str);
            strcpy(buffer, str);  
            send(sock, buffer, strlen(buffer), 0); 
        while (1){
            bzero(buffer, 1024);
            recv(sock, buffer, sizeof(buffer), 0); // Enter your name 
            printf("%s\n", buffer); 
            
            bzero(buffer, 1024); 
            scanf("%s", str);
            strcpy(buffer, str); 
            send(sock, buffer, strlen(buffer), 0);       

            bzero(buffer, 1024); 
            recv(sock, buffer, sizeof(buffer), 0); // Add passenger 
            printf("%s\n", buffer); 
            
            bzero(buffer, 1024); 
            scanf("%s", str);
            strcpy(buffer, str); 
            send(sock, buffer, strlen(buffer), 0); 
            
            if (strcmp(str,"n") == 0)
                break;
        }
        recv(sock, &pnr, sizeof(pnr), 0);
        printf("PNR Number: %d\n", pnr); 
        
        bzero(buffer, 1024); 
        recv(sock, buffer, sizeof(buffer), 0); // Ticket Booked Successfully 
        printf("%s\n", buffer); 

        break;
    }
    close(sock); 
    printf("Have a safe journey\n"); 
    return 0; 
}
