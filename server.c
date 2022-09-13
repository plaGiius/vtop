#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main()
{
    FILE *fp;
    struct sockaddr_in server, client;
    int s, n;
    char b1[100], b2[100], b3[100], b4[100], a[100];
    s = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(s, (struct sockaddr *)&server, sizeof(server));
    n = sizeof(client);
    int x;
    recvfrom(s, &x, sizeof(x), 0, (struct sockaddr *)&client, &n);
    while (x == 1)
    {
        strcpy(b2, "");
        fp = fopen("domain_to_ip.txt", "r");
        recvfrom(s, b1, sizeof(b1), 0, (struct sockaddr *)&client, &n);
        // printf("%s",b1);
        while (!feof(fp))
        {
            fscanf(fp, "%s", a);
            if (strcmp(a, b1) == 0)
            {
                fscanf(fp, "%s", b2);
                break;
            }
        }
        if (strcmp(b2, "") == 0)
        {
            strcpy(b2, "not found");
        }
        fclose(fp);
        sendto(s, b2, sizeof(b2), 0, (struct sockaddr *)&client, n);
        recvfrom(s, b1, sizeof(b1), 0, (struct sockaddr *)&client, &n);
        printf("\n the ip address is %s\n", b1);
    }

    while (x == 2)
    {
        strcpy(b3, "");
        fp = fopen("ip_to_domain.txt", "r");
        recvfrom(s, b3, sizeof(b1), 0, (struct sockaddr *)&client, &n);
        // printf("%s",b1);
        while (!feof(fp))
        {
            fscanf(fp, "%s", a);
            if (strcmp(a, b1) == 0)
            {
                fscanf(fp, "%s", b3);
                break;
            }
        }
        if (strcmp(b3, "") == 0)
        {
            strcpy(b3, "not found");
        }
        fclose(fp);
        sendto(s, b3, sizeof(b3), 0, (struct sockaddr *)&client, n);
        recvfrom(s, b4, sizeof(b1), 0, (struct sockaddr *)&client, &n);
        printf("\n the domain name is %s\n", b4);
    }
    close(s);
}
