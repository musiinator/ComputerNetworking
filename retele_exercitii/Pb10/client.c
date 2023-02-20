#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int clientSocket, n, rez;
    char s1[102], s2[102], ch;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    /*Create the socket. The 3 arguments are: 1) internet domain
                                              2) stream socket
                                              3) default protocol(TCP in thi
    */
    serverAddr.sin_family = AF_INET;                        /* address familnet */
    serverAddr.sin_port = 8888;                             /* set port numb*/
    serverAddr.sin_addr.s_addr = inet_addr("192.168.0.143"); 

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof serverAddr) < 0)
        printf("Eroare la conectarea la server\n");

    printf("Introduceti sirul1:\n");
    gets(s1);
    printf("Introduceti sirul2:\n");
    gets(s2);
    printf("Trimit la server sirurile...\n");
    send(clientSocket, s1, sizeof(s1), 0);
    send(clientSocket, s2, sizeof(s2), 0);
    recv(clientSocket, &ch, sizeof(char), 0);
    recv(clientSocket, &rez, sizeof(int), 0);

    printf("Am primit caracterul: %c\n", ch);
    printf("Cu numarul de aparitii: %d\n", rez);

    close(clientSocket);

    return 0;
}
