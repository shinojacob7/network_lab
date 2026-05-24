#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFER 1024
int main()
{
	int server_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len=sizeof(client_addr);
	char buffer[BUFFER];
	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(server_fd<0)
	{
		perror("socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("bind failed");
		exit(1);
	}
	printf("server listening\n");
	while(1)
	{
		memset(buffer,0,BUFFER);
		recvfrom(server_fd,buffer,BUFFER,0,(struct sockaddr*)&server_addr,&addr_len);
		printf("Received: %s",buffer);
		sendto(server_fd,buffer,BUFFER,0,(struct sockaddr*)&server_addr,addr_len);
	}
	close(server_fd);
	return 0;
}
