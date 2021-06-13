#include <iostream>
#include <stdlib.h>

using namespace std;

void merge(int array[], int low, int mid, int high)
{
	int i, j, k;
	int L[100], H[100];

	int n1 = mid - low + 1;
	int n2 = high - mid;
	
	for(i=0;i<n1;i++)
		L[i] = array[low + i];
	
	for(i=0;i<n2;i++)
		H[i] = array[mid + 1 + i];
		
	i = 0;
	j = 0;
	k = low;
	
	while(i < n1 && j < n2)
	{
		if(L[i] <= H[j])
		{
			array[k] = L[i];
			i++;
		}
		else
		{
			array[k] = H[j];
			j++;
		}
		k++;
	}
	
	while(i < n1)
	{
		array[k] = L[i];
		i++;
		k++;
	}
	
	while(j < n2)
	{
		array[k] = H[j];
		j++;
		k++;
	}
}

void mergeSort(int array[], int low, int high)
{
	if(low < high)
	{
		int mid = low + (high - low) / 2;
		mergeSort(array, low, mid);
		mergeSort(array, mid+1, high);
		merge(array, low, mid, high);
	}	
}

int main()
{
	int n, ntapes, i, j, k, c, col=0;
	int **tapes, *array;
	double *store_mrt;
	double MRT=0, mrt=0, sum=0;
	
	cout<<"\nEnter number of tapes : ";
	cin>>ntapes;
	
	cout<<"\nEnter number of elements : ";
	cin>>n;

	array = new int[n];
	
	if(n%ntapes==0)
		c = (n/ntapes);
	
	else
		c = (n/ntapes)+1;
	
	tapes = new int*[ntapes];
	
	for(i=0;i<ntapes;i++)
		tapes[i] = new int[c];
	
	cout<<"\nEnter elements :\n\n";
	
	for(i=0;i<n;i++)
	{
		cout<<"Element no. "<<i+1<<" : ";
		cin>>array[i];
	}

	cout<<c<<endl;
	
	mergeSort(array, 0, n-1);
	k = 0;
	
	for(i=0;i<ntapes;i++)
		for(j=0;j<c;j++)
			tapes[i][j] = -1;

	for(i=0;i<c;i++)
	{
		for(j=0;j<ntapes;j++)
		{
			if(k<n)
			{			
				tapes[j][i] = array[k];
				k++;
			}
		}
	}
	
	for(i=0;i<ntapes;i++)
	{
		for(j=0;j<c;j++)
		{
			cout<<tapes[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<"\n|Tape number\t|Mean Retrieval Time"<<"\t|\n";
	store_mrt = new double[ntapes];
	
	for(i=0;i<ntapes;i++)
	{
		sum=0;
		col=0;
		for(j=0;j<c;j++)
		{
			if(tapes[i][j]!=-1)
			{
				sum += tapes[i][j];
				col++;	
			}
		}

		if(col!=0)
			mrt = sum/col;
		
		else
			mrt = 0;
		
		store_mrt[i] = mrt;
		MRT += mrt;
		
		cout<<"|\t"<<i+1<<"\t|"<<mrt<<"\t\t\t|"<<endl;
	}
	
	cout<<"\nTotal mean retrieval time = (";
	
	for(i=0;i<ntapes;i++)
	{
		cout<<store_mrt[i];
		if(i!=ntapes-1)
			cout<<"+";
	}
	
	cout<<")/"<<ntapes<<" = "<<MRT/ntapes<<endl;

	return 0;
}

/*
OUTPUT

Enter number of tapes : 3
Enter number of elements : 8
Enter elements :
Element no. 1 : 2
Element no. 2 : 6
Element no. 3 : 1
Element no. 4 : 9
Element no. 5 : 10
Element no. 6 : 4
Element no. 7 : 7
Element no. 8 : 90
3
1 6 10
2 7 90
4 9 -1

|Tape number    |Mean Retrieval Time    |
|       1       |5.66667                        |
|       2       |33                     |
|       3       |6.5                    |

Total mean retrieval time = (5.66667+33+6.5)/3 = 15.0556
*/