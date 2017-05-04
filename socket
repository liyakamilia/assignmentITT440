#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include <error.h>
//#include <strings.h>
#include <string.h>
#include <unistd.h>
//#include <arpa/inet.h>
#include <netdb.h>

#define MAX_CLIENTS	5
#define MAX_DATA	1024

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int new;
	int sockaddr_len = sizeof(struct sockaddr_in);
	int data_len;
	char data[MAX_DATA];

	sock = socket(AF_INET, SOCK_STREAM, 0); //create socket
	if(sock < 0)
	{
		perror("Failed to create socket");
		exit(1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(1026);
	server.sin_addr.s_addr = INADDR_ANY;
	//bzero(&server.sin_zero, 8);

	//call bind
	if((bind(sock, (struct sockaddr *)&server, sockaddr_len))/* < 0*/)
	{
		perror("Bind failed");
		exit(1);
	}

	if((listen(sock, MAX_CLIENTS)) < 0) //listen
	{
		perror("Failed to listen");
		exit(-1);
	}

	//accept
	do //Better signal handling required
	{
		new = accept(sock, (struct sockaddr *)&client, &sockaddr_len);
		if(new == -1)
		{
			perror("Accept failed");
			//exit(1);
		}

		//printf("New client connected from port no %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));

		//data_len = 1;

		//while(data_len) {}
		else
		{
			printf("New client connected from port no %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
			data_len = 1;
			memset(data, 0, MAX_DATA);

			if ((data_len = recv(new, data, MAX_DATA, 0)) < 0)
				perror("Reading stream message error");
			else if(data_len == 0)
				printf("Client disconnected\n");
			else
				printf("Sent message: %s", data);

			send(new, data, data_len, 0);
			data[data_len] = '\0';
			printf("Sent message: %s", data);
			close(new);
		}
	} while(1);

	close(sock);
	return 0;
}
