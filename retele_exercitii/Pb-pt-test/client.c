#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int clientSocket, nr, rez, stop = 0;
    char cuv[102], raspuns[3];
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    /*Create the socket. The 3 arguments are: 1) internet domain
                                              2) stream socket
                                              3) default protocol(TCP in thi
    */
    serverAddr.sin_family = AF_INET;                        /* address familnet */
    serverAddr.sin_port = atoi(argv[2]);                             /* set port numb*/
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof serverAddr) < 0)
        printf("Eroare la conectarea la server\n");
    else
    {
        printf("Introduceti cuvantul:");
        gets(cuv);

        printf("Trimit la server cuvantul: %s\n", cuv);
        send(clientSocket, cuv, sizeof(cuv), 0);

        int ok = 0, ok2 = 0;
        int cnt = 1;
        int p = 0; //stabileste daca clientul a dat deja un numar sau nu

        while (!ok && cnt <= 5 && !stop)
        {
            printf("Introduceti numarul: ");
            scanf("%d", &nr);
            send(clientSocket, &nr, sizeof(int), 0);
            send(clientSocket, &cnt, sizeof(int), 0);
            recv(clientSocket, &ok, sizeof(int), 0);
            if (ok == 1)
            {
                printf("\nAm ghicit numarul!\n");
            }
            else
            {
                printf("\nRaspunsul dvs este(da/nu): ");
                scanf("%s", raspuns);
                send(clientSocket, raspuns, sizeof(raspuns), 0);
            }
            recv(clientSocket, &stop, sizeof(int), 0);
            recv(clientSocket, &cnt, sizeof(int), 0);
        }
    }

    close(clientSocket);

    return 0;
}
