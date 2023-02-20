#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int clientSocket, nr, rez, id_joc;
    char litera, cuv[102], ch, litera2;
    struct sockaddr_in serverAddr;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    /*Create the socket. The 3 arguments are: 1) internet domain
                                              2) stream socket
                                              3) default protocol(TCP in this case
    */
    serverAddr.sin_family = AF_INET;                        /* address familnet */
    serverAddr.sin_port = atoi(argv[2]);                             /* set port numb*/
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof serverAddr) < 0)
        printf("Eroare la conectarea la server\n");
    else
    {
        recv(clientSocket, &id_joc, sizeof(int), 0);
        printf("Am primit de la server id-ul jocului: %d\n", id_joc);
        
        recv(clientSocket, &litera, sizeof(litera), 0);
        printf("Am primit de la server litera: %c\n", litera);

        printf("Introduceti un cuvant care sa contina litera: %c\n", litera);
        gets(cuv);
      
        srand(time(NULL));

        litera2 = 'a' + (rand() % 26);

        printf("Trimit la server cuvantul: %s\n", cuv);
        send(clientSocket, cuv, sizeof(cuv), 0);
        printf("Si litera: %c\n", litera2);
        send(clientSocket, &litera2, sizeof(litera2), 0);
        

        recv(clientSocket, cuv, sizeof(cuv), 0);
        printf("Am primit de la server cuvantul: %s\n", cuv);
        recv(clientSocket, &litera2, sizeof(litera2), 0);
        printf("Am primit de la server litera: %c\n", litera2);
    }

    close(clientSocket);

    return 0;
}
