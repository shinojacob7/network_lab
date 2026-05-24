#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define BUFFER 1024
#define PORT 8080
int main()
{
	int server_fd,client_fd;
	char buffer[BUFFER];
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_len=sizeof(client_addr);
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd<0)
	{
		perror("Socket creation failed");
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
	listen(server_fd,5);
	client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addr_len);
	read(client_fd,buffer,BUFFER);
	printf("received string: %s",buffer);
	int len=strlen(buffer);
	printf("%d",len);
	for(int i=0;i<len/2;i++)
	{
		char temp=buffer[i];
		buffer[i]=buffer[len-i-1];
		buffer[len-i-1]=temp;
	}
	printf("returning string: %s",buffer);
	write(client_fd,buffer,strlen(buffer));
	close(client_fd);
	close(server_fd);
	return(0);
}
	
