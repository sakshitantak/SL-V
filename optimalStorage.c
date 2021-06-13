#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void inputJobs(int J[], int jobs)
{
	int i = 0;
	for(i=0;i<jobs;i++)
	{
		printf("\nLength of Job %d : ",i+1);
		scanf("%d",&J[i]);
	}
}

void displayJobs(int J[], int jobs)
{
	int i = 0;
	printf("\n");
	for(i=0;i<jobs;i++)
		printf("--------");
	
	printf("\n|");
	
	for(i=0;i<jobs;i++)
		printf("%d\t|",J[i]);
		
	printf("\n");
		
	for(i=0;i<jobs;i++)
		printf("--------");
		
	printf("\n");

}

void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	i = 0; 
	j = 0;  
	k = l; 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		int m = l+(r-l)/2; 

		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
	} 
} 

void optimalStorage(int T[], int tapes, int J[], int jobs)
{
	int i = 0;
	int j = 0;
	int rt[tapes];
	
	for(i=0;i<jobs;i++)
	{
		T[j] = J[i];
		j=(j+1)%tapes;
	}
	
}

void displayTapes(int T[], int tapes)
{
	int i = 0;
	for(i=0;i<tapes;i++)
	{
		printf("%d\t",T[i]);
	}
}

int main()
{
	int T[MAX];					//n tapes
	int jobs[MAX];				//m jobs
	int maxJobs = 0;			
	int maxTapes = 0;
	int i = 0;
	int j = 0;
	
	printf("\nStarting Optimal Storage ...");
	
	printf("\nEnter the number of tapes (<10) : ");
	scanf("%d",&maxTapes);
	
	printf("\n\nEnter the number of jobs to be written to the tapes (<100) : ");
	scanf("%d",&maxJobs);

	printf("\n\nInput of jobs");
	inputJobs(jobs, maxJobs);
	
	printf("\n\nJobs");
	displayJobs(jobs, maxJobs);
	
	printf("\n");
	
	mergeSort(jobs, 0, maxJobs-1);
	
	printf("\nSorted jobs\n");
	displayJobs(jobs, maxJobs);
	
	printf("\n\nCalling optimalStorage()");
	optimalStorage(T, maxTapes, jobs, maxJobs);
	printf("\nTapes\n");
	displayTapes(T, maxTapes);
	
}
