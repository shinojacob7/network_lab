#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#define PORT 8080
int main()
{
	int sock;
	struct sockaddr_in server_addr;
	socklen_t addr_len=sizeof(server_addr);
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("Socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	struct timeval tv;
	tv.tv_sec=2;
	tv.tv_usec=0;
	setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	int frame=0,ack;
	while(frame<5)
	{
		printf("Sending frame %d\n",frame);
		sendto(sock,&frame,sizeof(frame),0,(struct sockaddr*)&server_addr,addr_len);
		if(recvfrom(sock,&ack,sizeof(ack),0,(struct sockaddr*)&server_addr,&addr_len)<0)
		{
			printf("timeout");
		}
		else if(ack==frame)
		{
			printf("Success received ACK %d\n",ack);
			frame++;
		}
	}
	close(sock);
	return 0;
}

