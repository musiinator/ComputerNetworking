#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define SERVER "192.168.0.143" 

char sir[102], rez[204], ip[102];
int x, n, suma;

int main(int argc, char* argv[])
{
    struct sockaddr_in serveraddr, clientaddr;
    int s, i, newPort, slen = sizeof(serveraddr), suma, nrClienti, maxx;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    printf("Lungimea sirului: ");
    scanf("%d", &n);
    sendto(s, &n, sizeof(int), 0, (struct sockaddr*)&serveraddr, slen);
    printf("Trimit sirul...\n");
    for (i = 0; i < n; i++) {
        printf("x = ");
        scanf("%d", &x);
        sendto(s, &x, sizeof(int), 0, (struct sockaddr*)&serveraddr, slen);
    }


    recvfrom(s, &suma, sizeof(suma), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit suma: %d\n", suma);

    recvfrom(s, &nrClienti, sizeof(nrClienti), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit numarul de clienti anteriori: %d\n", nrClienti);

    recvfrom(s, &maxx, sizeof(maxx), 0, (struct sockaddr*)&clientaddr, &slen);
    printf("Am primit cel mai mare numar trimis vreodata: %d\n", maxx);

    close(s);
    return 0;
}