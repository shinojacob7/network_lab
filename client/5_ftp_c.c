#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFER 1024
int main()
{
	int sock;
	int len;
	struct sockaddr_in server_addr;
	socklen_t addr_len=sizeof(server_addr);
	char command[BUFFER],buffer[1024],filename[BUFFER];
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	if(connect(sock,(struct sockaddr*)&server_addr,addr_len)<0)
	{	
		perror("connect failed");
		exit(1);
	}
	printf("Enter command: ");
	fgets(command,BUFFER,stdin);
	write(sock,command,strlen(command));
	sscanf(command,"%s %s",buffer,filename);
	if(strcmp(buffer,"GET")==0)
	{
		FILE *fp=fopen(filename,"w");
		memset(buffer,0,BUFFER);
		while(read(sock,buffer,BUFFER))
		{
			printf("%s\n",buffer);
			fputs(buffer,fp);
		}
		fclose(fp);
	}
	if(strcmp(buffer,"PUT")==0)
	{
		FILE *fp=fopen(filename,"r");
		//memset(buffer,0,BUFFER);
		while(fgets(buffer,BUFFER,fp))
		{
			write(sock,buffer,strlen(buffer));
		}
		fclose(fp);
	}
	close(sock);
	return 0;
}
	
