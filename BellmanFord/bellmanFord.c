#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct edge{
	int src;
	int dest;
	int wt;
}edge;

typedef struct graph{
	int vertices;
	int edges;
	struct* edge e;
}graph;

edge* createGraph(int v, int e)
{
	graph* G = new graph;
}
