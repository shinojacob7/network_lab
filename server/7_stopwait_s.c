#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#define PORT 8080
int main()
{
	int server_fd;
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_len=sizeof(client_addr);
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
	int expect=0,frame;
	while(expect<5)
	{
		recvfrom(server_fd,&frame,sizeof(frame),0,(struct sockaddr*)&client_addr,&addr_len);
		if(frame==expect)
		{
			printf("Received frame %d\n",frame);
			if(frame==2)
			{
				printf("Dropping ACK for frame 2\n");
				expect++;
				continue;
			}
			printf("Sending ACK %d\n",frame);
			sendto(server_fd,&frame,sizeof(frame),0,(struct sockaddr*)&client_addr,addr_len);
			expect++;
		}
		else
		{
			printf("Received duplicate Frame %d, resending ACK \n",frame);
			sendto(server_fd,&frame,sizeof(frame),0,(struct sockaddr*)&client_addr,addr_len);
		}
	}
	close(server_fd);
	return 0;
}
	
			
