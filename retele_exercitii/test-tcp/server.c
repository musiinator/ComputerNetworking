#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int id_joc = 0;

void deservire_client(int newSocket1, int newSocket2) {
	int rez, lungime_sir, random, sum = 0, nr, cnt = 0, stop = 0;
	char litera, litera2, cuv[102];

	printf("Trimit catre clienti id-ul jocului: %d...\n", id_joc);
	send(newSocket1, &id_joc, sizeof(int), 0);
	send(newSocket2, &id_joc, sizeof(int), 0);

	srand(time(NULL));

	litera = 'a' + (rand() % 26);

	printf("Trimit catre clientul 1 litera: %c...\n", litera);

	send(newSocket1, &litera, sizeof(litera), 0);

	recv(newSocket1, cuv, sizeof(cuv), 0);
	if (!strchr(cuv, &litera))
		printf("Jocul continua!\n");

	printf("Am primit de la clientul 1 cuvantul: %s\n", cuv);

	recv(newSocket1, &litera2, sizeof(litera2), 0);

	printf("Am primit de la clientul 1 litera: %c\n", litera2);

	printf("Trimit cuvantul clientului 2: %s\n", cuv);
	send(newSocket2, cuv, sizeof(cuv), 0);
	printf("Trimit litera noua clientului 2: %c\n", litera2);
	send(newSocket2, &litera2, sizeof(litera2), 0);

	

	
	close(newSocket1);
	close(newSocket2);
}

int main() {
	int welcomeSocket, newSocket1, newSocket2;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);				/* Create the socket. The three arguments are:  1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */

	serverAddr.sin_family = AF_INET;						/* Address family = Internet */
	serverAddr.sin_port = 1234;							/* Set port number*/
	//serverAddr.sin_addr.s_addr = inet_addr("172.30.116.71");				/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	bind(welcomeSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));	/* Bind the address struct to the socket */

	listen(welcomeSocket, 5);							/* Listen on the socket, with 5 max connection requests queued */

	addr_size = sizeof serverStorage;
	while (1)
	{
		id_joc++;
		newSocket1 = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);
		printf("\nS-a conectat client 1.\n");
		printf("\nSe asteapta client 2...\n");
		newSocket2 = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);
		printf("\nS-au conectat 2 clienti. Incepe jocul...\n");
		if (fork() == 0) {
			deservire_client(newSocket1, newSocket2);
		}
	}
	close(welcomeSocket);

	return 0;
}