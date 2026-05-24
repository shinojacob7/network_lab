#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
int main()
{
	int sock;
	struct sockaddr_in server_addr,client_addr;
	socklen_t addr_len=sizeof(client_addr);
	int num[2],sum;
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	{
		perror("socket creation failed");
		exit(1);
	}
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	if(bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		perror("bind failed");
		exit(1);
	}
	recvfrom(sock,num,sizeof(num),0,(struct sockaddr*)&client_addr,&addr_len);
	printf("received nummbers: %d %d\n",num[0],num[1]);
	sum=num[0]+num[1];
	sendto(sock,&sum,sizeof(sum),0,(struct sockaddr*)&client_addr,addr_len);
	close(sock);
	return 0;
}
