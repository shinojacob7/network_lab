#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFER_S 1024
int main()
{
	int server_fd,client_fd;
	struct sockaddr_in client_addr, server_addr;
	socklen_t addr_len;
	char buffer[BUFFER_S];
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd<0)
	{
		perror("creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	if(bind(server_fd,(struct sockaddr *)&server_addr , sizeof(server_addr))<0)
	{
		perror("bind failed");
		exit(1);
	}
	printf("server listening");
	listen(server_fd,5);
	addr_len=sizeof(client_addr);
	client_fd=accept(server_fd,(struct sockaddr *)&client_addr ,&addr_len);
	if(client_fd<0)
	{
		perror("accept failed");
		exit(1);
	}
	while(1)
	{
		memset(buffer,0,BUFFER_S);
		int bytes=recv(client_fd,buffer,BUFFER_S,0);
		if(bytes<0)
			break;
		printf("recieved %s",buffer);
		send(client_fd,buffer,bytes,0);
	}
	close(client_fd);
	close(server_fd);
	return 0;
}
