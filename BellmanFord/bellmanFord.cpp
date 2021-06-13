#include <iostream>
#include <string>
using namespace std;

typedef struct edge{
	int src;
	int dest;
	int wt;
}edge;

typedef struct graph{
	int vertices;
	int edges;
	struct edge *e;
}graph;

graph* createGraph(int v, int e)
{
	graph* G = new graph;
	G->vertices = v;
	G->edges = e;
	G->e = new edge[e];
	return G;
}


void printArray(int distance[], int n)
{
	cout<<"\nPrntArray";
	cout<<"\nVertex"<<"\t"<<"Distance from source";
	for(int i=0;i<n;i++)
		cout<<"\n"<<i<<"\t"<<distance[i];
}

void bellmanFord(graph* G, int src)
{
	int v = G->vertices;
	int e = G->edges;
	int distance[v];
	
	for(int i=0;i<v;i++)
		distance[i] = 999;
	distance[src] = 0;
	
	for(int i=1;i<=v-1;i++)
	{
		for(int j=0;j<e;j++)
		{
			int u = G->e[j].src;
			int v = G->e[j].dest;
			int weight = G->e[j].wt;
			if(distance[u] != 999 && distance[u] + weight < distance[v])
				distance[v] = distance[u] + weight; 
		}
	}
		
	for(int i=0;i<e;i++)
	{
		int u = G->e[i].src;
		int v = G->e[i].dest;
		int weight = G->e[i].wt;
		cout<<"\nInside for";
		
		if(distance[u] != 999 && distance[u] + weight < distance[v])
			cout<<"\nGraph contains negative cycle!";
	}
	printArray(distance, v);
}

int main()
{
	int v;
	int e;
	graph* G = createGraph(v, e);
	int i = 0;
	char c;
	
	cout<<"\nEnter number of vertices : ";
	cin>>v;
	
	cout<<"\nEnter number of edges : ";
	cin>>e;
	
	do{
		cout<<"\nEnter source : ";
		cin>>G->e[i].src;
		
		cout<<"\nEnter destination : ";
		cin>>G->e[i].dest;
		
		cout<<"\nEnter weight of edge : ";
		cin>>G->e[i].wt;
		i++;
		
		cout<<"\nPress 'Y' pr 'y' to add more edges! Press 'z' to stop adding edges!";
		cin>>c;
	}while(c == 'y' || c == 'Y');
	
	bellmanFord(G, 0);
	return 0;
}
