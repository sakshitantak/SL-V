#include <stdio.h>
#include <ctype.h>
#include <string.h>



void Nqueen(int,int);
int place(int,int);
void display(int);
int abs(int);
void init(int[]);

void init(int x[])
{
	int i = 0;
	for(i=0;i<100;i++)
		x[i] = -1;
}

void NQueen(int x[], int k, int n)
{
	int i;
	int j;
	
	for(i=1;i<=n;i++)
	{
		//printf("\n\nIteration %d for Queen %d!",i,k);
		if(place(x,k,i))
		{
			x[k] = i;
			
			if(k == n)
				display(n);
			else
				NQueen(k+1, n);
		}
	}
}

int place(int x[], int k, int i)
{
	int j;
	for(j=1;j<=k-1;j++)
	{
		if((x[j] == i) || (abs(x[j]-i) == abs(j-k)))
		{
			printf("\n\nCan't place Queen %d at [%d,%d]",k,k,i);
			return 0;
		}

	}
	
	return 1;
}

void display(int n)
{
	int i;
	int j;
	
	printf("\n\nThe Chess Board Solution is\n");
	printf("\t");
	
	for(i=1;i<=n;i++)
		printf("\t%d",i);
		
	printf("\n\t---------------------------------");
		
	for(i=1;i<=n;i++)
	{
		printf("\n\t%d|",i);
		for(j=1;j<=n;j++)
		{
			if(x[i] == j )
				printf("\tQ");
			else
				printf("\tx");
		}
	}
}

int abs(int i)
{
	if(i>=0)
		return i;
	else
		return (-1*i);
	
}

int main()
{
	int n;
	int x[100];
	
	init();	
	
	printf("\n\nEnter the number of queens you would like to place on the board (<4) : ");
	scanf("%d",&n);
			
	printf("\nCalling NQueen()...");
	NQueen(x,1,n);
}

/*
Enter the number of queens you would like to place on the board (<4) : 4

Calling NQueen()...

Can't place Queen 2 at [2,1]

Can't place Queen 2 at [2,2]

Can't place Queen 3 at [3,1]

Can't place Queen 3 at [3,2]

Can't place Queen 3 at [3,3]

Can't place Queen 3 at [3,4]

Can't place Queen 3 at [3,1]

Can't place Queen 4 at [4,1]

Can't place Queen 4 at [4,2]

Can't place Queen 4 at [4,3]

Can't place Queen 4 at [4,4]

Can't place Queen 3 at [3,3]

Can't place Queen 3 at [3,4]

Can't place Queen 2 at [2,1]

Can't place Queen 2 at [2,2]

Can't place Queen 2 at [2,3]

Can't place Queen 4 at [4,1]

Can't place Queen 4 at [4,2]

The Chess Board Solution is
		1	2	3	4
	---------------------------------
	1|	x	Q	x	x
	2|	x	x	x	Q
	3|	Q	x	x	x
	4|	x	x	Q	x

Can't place Queen 4 at [4,4]

Can't place Queen 3 at [3,2]

Can't place Queen 3 at [3,3]

Can't place Queen 3 at [3,4]

Can't place Queen 3 at [3,1]

Can't place Queen 3 at [3,2]

Can't place Queen 3 at [3,3]

Can't place Queen 4 at [4,1]

The Chess Board Solution is
		1	2	3	4
	---------------------------------
	1|	x	x	Q	x
	2|	Q	x	x	x
	3|	x	x	x	Q
	4|	x	Q	x	x

Can't place Queen 4 at [4,3]

Can't place Queen 4 at [4,4]

Can't place Queen 2 at [2,2]

Can't place Queen 2 at [2,3]

Can't place Queen 2 at [2,4]

Can't place Queen 3 at [3,1]

Can't place Queen 3 at [3,2]

Can't place Queen 4 at [4,1]

Can't place Queen 4 at [4,2]

Can't place Queen 4 at [4,3]

Can't place Queen 4 at [4,4]

Can't place Queen 3 at [3,4]

Can't place Queen 3 at [3,1]

Can't place Queen 3 at [3,2]

Can't place Queen 3 at [3,3]

Can't place Queen 3 at [3,4]

Can't place Queen 2 at [2,3]

Can't place Queen 2 at [2,4]
*/
