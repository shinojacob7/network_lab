#include<stdio.h>
#include<stdlib.h>
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
		perror("Socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("Bind failed");
		exit(1);
	}
	int expected=0,frame;
	int drop=1;
	while(expected<6)
	{
		recvfrom(server_fd,&frame,sizeof(frame),0,(struct sockaddr*)&client_addr,&addr_len);
		if(frame==2 && drop)
		{
			printf("Simulate error drop frame 2\n");
			drop=0;
			continue;
		}
		if(frame==expected)
		{
			printf("Received frame %d\n",frame);
			printf("Sending ACK %d\n",frame);
			sendto(server_fd,&frame,sizeof(frame),0,(struct sockaddr*)&client_addr,addr_len);
			expected++;
		}
		else
		{
			int last_ack=expected-1;
			printf("Out of order\n");
			if(last_ack>=0)
			{
				printf("Resending last good ACK %d\n",last_ack);
				sendto(server_fd,&last_ack,sizeof(last_ack),0,(struct sockaddr*)&client_addr,addr_len);
			}
		}
	}
	close(server_fd);
	return 0;
}
