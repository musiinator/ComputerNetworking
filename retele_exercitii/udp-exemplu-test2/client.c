#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define SERVER "192.168.0.143" 

char sir[102], rez[204], ip[102];

int main(int argc, char* argv[])
{
    struct sockaddr_in serveraddr, clientaddr;
    int s, i, newPort, slen = sizeof(serveraddr), suma;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

    printf("Trimit sirul: ");
    gets(sir);
    sendto(s, sir, sizeof(sir), 0, (struct sockaddr*)&serveraddr, slen);


    recvfrom(s, &newPort, sizeof(newPort), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit noul port: %d\n", newPort);
    
    recvfrom(s, &suma, sizeof(suma), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit suma: %d\n", suma);
    
    recvfrom(s, ip, sizeof(ip), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit ip-ul: %s\n", ip);
    close(s);
    return 0;
}