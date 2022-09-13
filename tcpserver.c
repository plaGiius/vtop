#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <arpa/inet.h> 

int main(){ 
    char *ip = "127.0.0.1"; 
    int port = 5566; 
    int server_sock, client_sock; 
    struct sockaddr_in server_addr, client_addr; 
    socklen_t addr_size; 
    char buffer[1024]; 
    int n; 
    int pnr;
    server_sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sock < 0){
        perror("[-]Socket error"); 
        exit(1); 
    } 
    //printf("[+]TCP server socket created.\n"); 
    memset(&server_addr, '\0', sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = port; 
    server_addr.sin_addr.s_addr = inet_addr(ip); 
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
    if (n < 0){ 
        perror("[-]Bind error"); 
        exit(1); 
    } 
    //printf("[+]Bind to the port number: %d\n", port); 
    printf("IRCTC Server\n\n");
    listen(server_sock, 5); 
    //printf("Listening...\n"); 
    while(1){ 
        addr_size = sizeof(client_addr); 
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size); 
        while (1){
            bzero(buffer, 1024); 
		strcpy(buffer, "Enter Boarding Point"); 
		send(client_sock, buffer, strlen(buffer), 0); 

		bzero(buffer, 1024); 
		recv(client_sock, buffer, sizeof(buffer), 0); 
		printf("Boarding Station: %s\n", buffer); 

		bzero(buffer, 1024); 
		strcpy(buffer, "Enter Dropping Point"); 
		send(client_sock, buffer, strlen(buffer), 0); 
		bzero(buffer, 1024); 

		recv(client_sock, buffer, sizeof(buffer), 0); 
		printf("Dropping Station: %s\n", buffer); 
            while(1){
                bzero(buffer, 1024); 
                strcpy(buffer, "Enter your name"); 
                send(client_sock, buffer, strlen(buffer), 0);

                bzero(buffer, 1024); 
                recv(client_sock, buffer, sizeof(buffer), 0);
                printf("Passenger Name: %s\n", buffer);
                
                bzero(buffer, 1024); 
                strcpy(buffer, "Add Passenger [y/n]"); 
                send(client_sock, buffer, strlen(buffer), 0); 

                bzero(buffer, 1024); 
                recv(client_sock, buffer, sizeof(buffer), 0);
                if (strcmp(buffer, "n") == 0)
                    break;
                
            }

            //sleep(2);
            pnr = rand();
            send(client_sock, &pnr, sizeof(pnr), 0);
            printf("PNR Number: %d\n", pnr);

            //sleep(2);
            bzero(buffer, 1024); 
            strcpy(buffer, "Ticket Booked Successfully");
            send(client_sock, buffer, strlen(buffer), 0);
            printf("i");
            close(client_sock); 
            break;
        } 
    }
    return 0; 
}
