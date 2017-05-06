#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
//#include <strings.h>
#include <string.h>
#include <netdb.h>
//#include <arpa/inet.h>

#define DATA "Hello World!"
#define BUFFER	1024

void main(int argc, char *argv[])
{
	struct sockaddr_in remote_server;
	struct hostent *hp;
	int sock;
	//char input[BUFFER];
	//char output[BUFFER];
	int len;

	sock = socket(AF_INET, SOCK_STREAM, 0); //create socket
	if(sock < 0)
	{
		perror("Failed to create socket");
		exit(1);
	}

	remote_server.sin_family = AF_INET;
	hp = gethostbyname(argv[1]);

	if(hp == 0)
	{
		perror("gethostbyname failed");
		close(sock);
		exit(1);
	}

	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	remote_server.sin_port = htons(1026);

	//remote_server.sin_addr.s_addr = INADDR_ANY;
	//bzero(&remote_server.sin_zero, 8);

	if((connect(sock, (struct sockaddr *)&remote_server, sizeof(remote_server))) < 0)
	{
		perror("Connect failed");
		exit(1);
	}

	if(send(sock, DATA, sizeof(DATA), 0) < 0)
	{
		perror("Sent failed");
		close(sock);
		exit(1);
	}

	/*while(1)
	{
		fgets(input, BUFFER, stdin);
		send(sock, input, strlen(input), 0);

		len = recv(sock, output, BUFFER, 0);
		output[len] = '\0';
		printf("%s\n", output);
	}*/
	
	printf("Sent %s\n", DATA);
	close(sock);

	return 0;
}
