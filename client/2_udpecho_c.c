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
	socklen_t addr_len=sizeof(server_addr);
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	while(1)
	{
		printf("Enter the message:");
		fgets(buffer,BUFFER,stdin);
		sendto(sock,buffer,BUFFER,0,(struct sockaddr*)&server_addr,addr_len);
		memset(buffer,0,BUFFER);
		recvfrom(sock,buffer,BUFFER,0,(struct sockaddr*)&server_addr,&addr_len);
		printf("Echo from server: %s\n",buffer);
	}
	close(sock);
	return 0;
}

