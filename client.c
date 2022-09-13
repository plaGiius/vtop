#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
int main()
{
    struct sockaddr_in server, client;
    int s, n;
    char b1[100], b2[100];
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    n = sizeof(server);
    int x;
    printf("Chose your choice :\n");
    printf("1.Domain to ip\n");
    printf("2.ip to Domain\n");
    printf("Enter your choice : ");
    scanf("%d", &x);
    sendto(s, &x, sizeof(x), 0, (struct sockaddr *)&server, n);
    while (x == 1)
    {
        printf("\nEnter the domain name: ");
        scanf("%s", b2);
        sendto(s, b2, sizeof(b2), 0, (struct sockaddr *)&server, n);
        recvfrom(s, b1, sizeof(b1), 0, NULL, NULL);
        sendto(s, b1, sizeof(b1), 0, (struct sockaddr *)&server, n);
        printf("\n the ip address is %s\n", b1);
    }
    
    while (x == 2)
    {
        printf("\nEnter the ip address: ");
        scanf("%s", b2);
        sendto(s, b2, sizeof(b2), 0, (struct sockaddr *)&server, n);
        recvfrom(s, b1, sizeof(b1), 0, NULL, NULL);
        sendto(s, b1, sizeof(b1), 0, (struct sockaddr *)&server, n);
        printf("\n the domain name is %s\n", b1);
    }

    close(s);
}
