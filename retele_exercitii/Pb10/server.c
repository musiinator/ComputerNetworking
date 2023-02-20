#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main() {
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);				/* Create the socket. The three arguments are:  1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */

	serverAddr.sin_family = AF_INET;						/* Address family = Internet */
	serverAddr.sin_port = 8888;							/* Set port number*/
	serverAddr.sin_addr.s_addr = inet_addr("192.168.0.143");				/* Set IP address to localhost */

	bind(welcomeSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));	/* Bind the address struct to the socket */

	listen(welcomeSocket, 5);							/* Listen on the socket, with 5 max connection requests queued */

	addr_size = sizeof serverStorage;
	while (1)
	{
		int max_ap = -1, rez, lungime_sir, fv[130];
		char ch, s1[102], s2[102];

		for (int i = 0; i <= 129; i++)
			fv[i] = 0;

		newSocket = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);

		printf("\nWaiting for clients...\n");

		recv(newSocket, s1, sizeof(s1), 0);						/* Read the message from the server into the buffer */
		recv(newSocket, s2, sizeof(s2), 0);						/* Read the message from the server into the buffer */
		if (strlen(s1) > strlen(s2))
			lungime_sir = strlen(s2);
		else lungime_sir = strlen(s1);

		for (int i = 0; i < lungime_sir; i++)
		{
			if (s1[i] == s2[i])
				fv[s1[i]]++;
		}
		for (int i=0; i<130; i++)
			if (fv[i])
				if (fv[i] > max_ap)
				{
					max_ap = fv[i];
					ch = (char)i;
				}
		printf("Data received: %s\n", s1);   					/* Print the received message */
		printf("Data received: %s\n", s2);   					/* Print the received message */
		
		rez = max_ap;
		printf("Trimit caracterul: %c\n", ch);
		send(newSocket, &ch, sizeof(char), 0);
		printf("Cu numarul de aparitii: %d\n", rez);
		send(newSocket, &rez, sizeof(int), 0);
	}
	close(newSocket);
	close(welcomeSocket);

	return 0;
}