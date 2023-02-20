#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define PORT 1234   

int cnt, newPort;
char sir[102], rez[204], adresaIP[102], ipVechi[102];

int main(void)
{
    struct sockaddr_in serveraddr, clientaddr;

    int s, s1, i, slen = sizeof(clientaddr), nr, suma = 0, sumaVeche = 0;


    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    int contor = 0;
    while (1)
    {
        printf("\nWaiting for data...\n");
        recvfrom(s, sir, sizeof(sir), 0, (struct sockaddr*)&clientaddr, &slen);
        adresaIP[0] = '\0';
        strcat(adresaIP, inet_ntoa(clientaddr.sin_addr));

        printf("Am primit sirul %s\n", sir);
        suma = 0;
        nr = 0;
        for (int i = 0; i < strlen(sir); i++) {
            if (sir[i] != 32)
                nr = nr * 10 + sir[i] - '0';
            else
            {
                suma += nr;
                nr = 0;
            }
        }
        suma += nr;
        srand(time(NULL));
        newPort = rand() % 9000 + 1000;
        sendto(s, &newPort, sizeof(newPort), 0, (struct sockaddr*)&clientaddr, slen);
        printf("Am trimis noul port %d\n", newPort);

        s1 = socket(AF_INET, SOCK_DGRAM, 0);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(newPort);
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(s1, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        
        if (!contor)
        {
            printf("Trimit suma: %d\n", suma);
            sendto(s, &suma, sizeof(suma), 0, (struct sockaddr*)&clientaddr, slen);
            printf("Trimit ip-ul: %s\n", adresaIP);
            sendto(s, adresaIP, sizeof(adresaIP), 0, (struct sockaddr*)&clientaddr, slen);
        }
        else
        {
            printf("Trimit suma anterioara: %d\n", sumaVeche);
            sendto(s1, &sumaVeche, sizeof(sumaVeche), 0, (struct sockaddr*)&clientaddr, slen);
            printf("Trimit ip-ul anterior: %s\n", ipVechi);
            sendto(s1, ipVechi, sizeof(ipVechi), 0, (struct sockaddr*)&clientaddr, slen);
        }
        contor++;
        sumaVeche = suma;
        ipVechi[0] = '\0';
        strcat(ipVechi, adresaIP);
    }
    close(s);
    close(s1);
    return 0;
}
