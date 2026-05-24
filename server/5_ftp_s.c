#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define BUFFER 1024
int main()
{
	int server_fd,client_fd;
	int len;
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_len=sizeof(client_addr);
	char buffer[BUFFER],command[BUFFER],filename[BUFFER];
	server_fd=socket(AF_INET,SOCK_STREAM,0);
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
	listen(server_fd,5);
	client_fd=accept(server_fd,(struct sockaddr*)&client_addr,&addr_len);
	read(client_fd,command,BUFFER);
	sscanf(command,"%s %s",buffer,filename);
	if(strcmp(buffer,"GET")==0)
	{
		FILE *fp=fopen(filename,"r");
		//memset(buffer,0,BUFFER);
		if(fp==NULL)
		{
			write(client_fd,"ERROR",5);
		}
		else
		{
			 while(fgets(buffer,BUFFER,fp))
			 {
			 	write(client_fd,buffer,strlen(buffer));
			 }
			 fclose(fp);
		}
	}
	if(strcmp(buffer,"PUT")==0)
	{
		FILE *fp=fopen(filename,"w");
		memset(buffer,0,BUFFER);
		while(read(client_fd,buffer,BUFFER))
		{
			printf("%s\n",buffer);
			fputs(buffer,fp);
		}
		fclose(fp);
	}
	close(client_fd);
	close(server_fd);
	return 0;
}
	
