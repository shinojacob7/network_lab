#include<stdio.h>
#include<stdlib.h>
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
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	struct timeval tv;
	tv.tv_sec=2;
	tv.tv_usec=0;
	setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	int base=0;
	int next_seq=0;
	int window_size=3;
	int total_frame=6;
	int ack;
	while(base<total_frame)
	{
		while(next_seq<base+window_size && next_seq<total_frame)
		{
			printf("Sending frame %d \n",next_seq);
			sendto(sock,&next_seq,sizeof(next_seq),0,(struct sockaddr*)&server_addr,addr_len);
			next_seq++;
		}
		if(recvfrom(sock,&ack,sizeof(ack),0,(struct sockaddr*)&server_addr,&addr_len)<0)
		{
			printf("Timeout frame %d\n",base);
			next_seq=base;
		}
		else
		{
			printf("Success Received ACK %d\n",ack);
			if(ack>=base)
			{
				base=ack+1;
			}
		}
	}
	printf("All succesfull\n");
	close(sock);
	return 0;
}

