#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
int main()
{
	int sock;
	int num[2],sum;
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
	printf("Enter the numbers to add:");
	scanf("%d %d",&num[0],&num[1]);
	sendto(sock,num,sizeof(num),0,(struct sockaddr*)&server_addr,addr_len);
	recvfrom(sock,&sum,sizeof(sum),0,(struct sockaddr*)&server_addr,&addr_len);
	printf("Sum of numbers: %d\n",sum);
	close(sock);
	return 0;
}
	
