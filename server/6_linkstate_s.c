#include<stdio.h>
#define INF 999
int main()
{
	int n,source;
	int cost[20][20],distance[20],visited[20];
	printf("Enter the no of the nodes:");
	scanf("%d",&n);
	printf("Enter the cost matrix:(999 for no path)\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			scanf("%d",&cost[i][j]);
		}
	}
	printf("Enter the source:");
	scanf("%d",&source);
	for(int i=0;i<n;i++)
	{
		distance[i]=cost[source][i];
		visited[i]=0;
	}
	distance[source]=0;
	visited[source]=1;
	for(int i=0;i<n;i++)
	{
		int min=INF;
		int u=-1;
		for(int j=0;j<n;j++)
		{
			if(!visited[j] && distance[j]<min)
			{
				min=distance[j];
				u=j;
			}
		}
		visited[u]=1;
		for(int j=0;j<n;j++)
		{
			if(!visited[j] && distance[j]>distance[u]+cost[u][j])
			{
				distance[j]=distance[u]+cost[u][j];
			}
		}
	}
	printf("shortest distances:\n");
	for(int i=0;i<n;i++)
	{
		printf("shortest path to %d is %d\n",i,distance[i]);
	}
	return 0;
}
