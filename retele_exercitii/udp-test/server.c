#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define PORT 1234   

int sumcif(int n)
{
    int s = 0;
    while (n)
    {
        if (n % 2)
            s += n % 10;
        n /= 10;
    }
    return s;
}

int cnt, newPort, x, suma, n;
char rez[204], adresaIP[102], ipVechi[102];

int main(int argc, char* argv[])
{
    struct sockaddr_in serveraddr, clientaddr;

    int s, s1, i, slen = sizeof(clientaddr), nr, suma = 0, sumaVeche = 0;

    int port = atoi(argv[2]);
    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    int contor = 0;
    int maxx = -999999999;
    while (1)
    {
        printf("\nWaiting for data...\n");
        recvfrom(s, &n, sizeof(int), 0, (struct sockaddr*)&clientaddr, &slen);
        suma = 0;
        for (int i = 0; i < n; i++) {
            recvfrom(s, &x, sizeof(int), 0, (struct sockaddr*)&clientaddr, &slen);
            suma += sumcif(x);
        }
        printf("Suma cifrelor este: %d\n", suma);

        printf("Portul initial este: %d\n", port);
        newPort = port;
        newPort += suma;
        if (newPort > maxx)
            maxx = newPort;
        printf("Noul port este: %d\n", newPort);

        s1 = socket(AF_INET, SOCK_DGRAM, 0);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(newPort);
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(s1, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        printf("Trimit suma %d pe noul port creat\n", suma);
        sendto(s1, &suma, sizeof(suma), 0, (struct sockaddr*)&clientaddr, slen);
        printf("Trimit numarul clientilor anteriori: %d\n", contor);
        sendto(s1, &contor, sizeof(contor), 0, (struct sockaddr*)&clientaddr, slen);
        printf("Trimit cel mai mare numar trimis vreodata: %d\n", maxx);
        sendto(s1, &maxx, sizeof(maxx), 0, (struct sockaddr*)&clientaddr, slen);
        contor++;
    }
    close(s);
    close(s1);
    return 0;
}
