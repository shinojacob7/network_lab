#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFER_S 1024
int main()
{
	int server_fd;
	struct sockaddr_in server_addr;
	socklen_t addr_len;
	char buffer[BUFFER_S];
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd<0)
	{
		perror("creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	if(connect(server_fd,(struct sockaddr *)&server_addr , sizeof(server_addr))<0)
	{
		perror("bind failed");
		exit(1);
	}
	while(1)
	{
		printf("Enter message:");
		fgets(buffer,BUFFER_S,stdin);
		write(server_fd,buffer,strlen(buffer));
		memset(buffer,0,BUFFER_S);
		read(server_fd,buffer,BUFFER_S);
		printf("recieved %s",buffer);
	}
	close(server_fd);
	return 0;
}
