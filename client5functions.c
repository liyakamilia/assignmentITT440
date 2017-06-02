#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <netdb.h>
#include <sys/types.h>

#define MAX_HOSTNAME      255
 
int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct in_addr in;
    struct hostent *hp;
    char message[1000], hostbuffer[MAX_HOSTNAME+1];
    int la_len, ret, ret1, i, ret2, size, len;
    //char server_reply[2000];

    //gethostbyaddr() function
    //identify the fully qualified domain name of a host given its IP address
    inet_aton("192.168.1.1", &in);

    //output of gethostbyaddr() function
    if (hp = gethostbyaddr((char *)&in.s_addr, sizeof(in.s_addr), AF_INET)) {
        printf("Host name is %s\n", hp->h_name);
    }

    //gethostbyname() function
    //identify the IP address given a fully qualified domain name
    hp = gethostbyname("www.microsoft.com");

    printf("-----------------------------------------------------------");
    //output of gethostbyname() function
    if (hp) {
        printf("\nh_name is %s\n", hp->h_name);
        printf("h_addrtype is %d\n", hp->h_addrtype);

        i = 0;
        printf("Aliases:\n");
        while (1) {
            if (hp->h_aliases[i]) {
                printf("h_aliases[%d] = %s\n", i, hp->h_aliases[i]);
                i++;
            } else break;
        }

        i = 0;
        printf("Addresses:\n");
        while (1) {
            if (hp->h_addr_list[i]) {
                struct in_addr theAddr;
                memcpy(&theAddr.s_addr, hp->h_addr_list[i], sizeof(theAddr.s_addr));
                printf("h_addr_list[%d] = %s\n", i, inet_ntoa(theAddr));
                i++;
            } else break;
        }
    }
    
    //create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    //getsockopt() function
    //getting the send buffer size for a socket
    len = sizeof(size);

    ret2 = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&size, (socklen_t *)&len);
    printf("\nOutput of getsockopt() function is %s", ret2);

    //getsockname() function
    //return the local address of a given socket
    la_len = sizeof(server);
    
    ret = getsockname(sock, (struct sockaddr_in *)&server, &la_len);

    //gethostname() function
    //permits the application to identify the name of the host on which it executes
    ret1 = gethostname(hostbuffer, MAX_HOSTNAME);

    //setsockopt() function
    //setting the send buffer size for a socket
    //size = size * 2;
    //ret2 = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&size, sizeof(size));

    if (sock == -1)
    {
        printf("\nCouldn't create socket!");
    }
    puts("\n\nDone! Socket created");
     
    server.sin_addr.s_addr = inet_addr("192.168.8.131");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
 
    //connect to remote server
    if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Error! Connection failed");
        return 1;
    }
    puts("Connected\n");

    //output of getsockname() function
    if(ret == 0) {
        printf("Local address: %s\n", inet_ntoa(server.sin_addr));
        printf("Local port: %d\n", server.sin_port, "\n");
    }
    
    //output of gethostname() function
    if (ret1 == 0) {
        printf("Host name is %s\n", hostbuffer);
        printf("\n");
    }    

    //keep communicating with server
    /*while(1) {
        //printf("Enter message: ");
        //scanf("%s", message);
        
        //send data
        //if(send(sock, message, strlen(message), 0) < 0) {
            //puts("Error! Send message failed");
            //return 1;
        //}
         
        //receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        puts("Server reply :");
        puts(server_reply);
    }*/

    close(sock);
    return 0;
}
