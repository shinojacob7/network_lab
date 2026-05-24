#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define BUFFER 1024
#define PORT 8080
int main()
{
	int sock;
	char buffer[BUFFER];
	struct sockaddr_in server_addr;
	socklen_t addrlen=sizeof(server_addr);
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	if(connect(sock,(struct sockaddr*)&server_addr,addrlen)<0)
	{
		perror("connection failed");
		exit(1);
	}
	printf("Enter the string:");
	fgets(buffer,BUFFER,stdin);
	write(sock,buffer,strlen(buffer));
	memset(buffer,0,BUFFER);
	read(sock,buffer,BUFFER);
	printf("reversed string: %s",buffer);
	close(sock);
	return 0;
}
