#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define SERVER "192.168.0.143" 

char sir[102], rez[204], ip_sir[102];

int main(int argc, char *argv[])
{
    struct sockaddr_in serveraddr, clientaddr;
    int s, i, port, slen=sizeof(serveraddr);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Trimit sirul: ");
    gets(sir);
    sendto(s, sir, sizeof(sir), 0, (struct sockaddr*)&serveraddr, slen);


    recvfrom(s, &port, sizeof(port), 0, (struct sockaddr*)&clientaddr, &slen);
    recvfrom(s, rez, sizeof(rez), 0, (struct sockaddr*)&clientaddr, &slen);
    recvfrom(s, ip_sir, sizeof(ip_sir), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("%d %s %s", port, rez, ip_sir);
    close(s);                                                           
    return 0;
}