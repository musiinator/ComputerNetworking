#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>
 
#define PORT 1234   

int cnt, fv[150];
char sir[102], rez[204], ch[2];

int main(void)
{
    struct sockaddr_in serveraddr, clientaddr;

    int s, s1, i, slen = sizeof(clientaddr), nr;


    s = socket(AF_INET, SOCK_DGRAM, 0);

    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(s, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    while (1)
    {
        if (cnt) {
            rez[0] = '\0';
            for (int i = 0; i < strlen(sir); i++) {
                if(sir[i]!=32) fv[sir[i]]++;
            }
            for (int i = 0; i < 150; i++)
            {
                if (fv[sir[i]]>0) {
                    ch[0] = sir[i];
                    strcat(rez, ch);
                    strcat(rez, ",");
                    fv[sir[i]] = 0;
                }
            }
            strcpy(rez + strlen(rez) - 1, rez + strlen(rez));
        }
        cnt++;
        char ip_sir[102];
        ip_sir[0] = '\0';
        printf("\nWaiting for data...\n");
        recvfrom(s, sir, sizeof(sir), 0, (struct sockaddr*)&clientaddr, &slen);
        if (!(cnt - 1)) {
            strcat(ip_sir, "127.0.0.1");
            rez[0] = '\0';
            for (int i = 0; i < strlen(sir); i++) {
                if (sir[i] != 32) fv[sir[i]]++;
            }
            for (int i = 0; i < 150; i++)
            {
                if (fv[sir[i]] > 0) {
                    ch[0] = sir[i];
                    strcat(rez, ch);
                    strcat(rez, ",");
                    fv[sir[i]] = 0;
                }
            }
            strcpy(rez + strlen(rez) - 1, rez + strlen(rez));
        }
        int port = (int)ntohs(clientaddr.sin_port);
        printf("Am primit sirul %s, de la adresa %s, prin portul %d\n", sir, inet_ntoa(clientaddr.sin_addr), port);
        nr = 0;
        for (int i = 0; i < strlen(sir); i++) {
            if (sir[i] == 32) nr++;
        }

        port += nr;
        s1 = socket(AF_INET, SOCK_DGRAM, 0);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_port = htons(port);
        serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(s1, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
        printf("Trimit portul: %d...\n", port);
        sendto(s1, &port, sizeof(port), 0, (struct sockaddr*)&clientaddr, slen);
        printf("Trimit sirul: %s...\n", rez);
        sendto(s1, rez, sizeof(rez), 0, (struct sockaddr*)&clientaddr, slen);
        
        if(cnt-1)strcat(ip_sir, inet_ntoa(clientaddr.sin_addr));
        printf("Trimit ip-ul: %s...\n", ip_sir);
        sendto(s1, ip_sir, sizeof(ip_sir), 0, (struct sockaddr*)&clientaddr, slen);
    }
    close(s);
    close(s1);
    return 0;
}
