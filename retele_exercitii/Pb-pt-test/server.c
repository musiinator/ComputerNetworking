#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void deservire_client(int newSocket) {
	int rez, lungime_sir, random, sum = 0, nr, cnt = 0, stop = 0;
	char cuv[102], raspuns[3];
	int ok = 0, ok2 = 0;


	recv(newSocket, cuv, sizeof(cuv), 0);						/* Read the message from the server into the buffer */

	printf("Am primit cuvantul: %s\n", cuv);

	srand(time(NULL));

	for (int i = 0; i < 3; i++)
	{
		random = rand() % (strlen(cuv) - 1);
		sum = sum + cuv[random];
	}
	printf("Suma caracterelor ASCII din cuvant este: %d\n", sum);
	while (ok == 0 && cnt <= 5 && !stop)
	{
		recv(newSocket, &nr, sizeof(int), 0);
		recv(newSocket, &cnt, sizeof(int), 0);
		if (nr == sum)
		{
			ok = 1;
			if (cnt == 1)
			{
				printf("Clientul a ghicit numarul din prima incercare!\n");
			}
			else
			{
				printf("Clientul a ghicit numarul din a %d-a incercare!\n", cnt);
			}
		}
		else
		{
			ok = 0;
		}
		send(newSocket, &ok, sizeof(int), 0);
		if (!ok)
		{
			printf("Numar incorect. Doriti sa continuati?\n");
			recv(newSocket, raspuns, sizeof(raspuns), 0);
			if (!strcmp(raspuns, "nu") || !strcmp(raspuns, "NU"))
			{
				if (cnt == 1)
					printf("Sfarsit. Ati folosit o incercare!\n");
				else
					printf("Sfarsit. Ati folosit %d incercari!\n", cnt);
				stop = 1;
			}
			if (strcmp(raspuns, "nu") && strcmp(raspuns, "NU") && strcmp(raspuns, "da") && strcmp(raspuns, "DA"))
				printf("Raspuns invalid!\n");
		}
		send(newSocket, &stop, sizeof(int), 0);
		cnt++;
		send(newSocket, &cnt, sizeof(int), 0);
	}
	if (!ok && !stop)
		printf("S-a depasit numarul de incercari!\n");
	ok = 0;
	cnt = 0;
	close(newSocket);
}

int main() {
	int welcomeSocket, newSocket;
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

		newSocket = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);

		printf("\nWaiting for clients...\n");
		if (fork() == 0) {
			deservire_client(newSocket);
		}
		
	}
	close(welcomeSocket);

	return 0;
}