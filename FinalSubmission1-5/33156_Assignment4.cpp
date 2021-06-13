#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct data
{
	int max, min;
	int *arr;
}data;

data MaxMin(int low, int high, data dat)
{
	if(low == high)
	{
		dat.max = dat.arr[low];
		dat.min = dat.arr[low];
	}
	else if(low == (high - 1))
	{
		if(dat.arr[low]<dat.arr[high])
		{
			dat.max = dat.arr[high];
			dat.min = dat.arr[low];
		}

		else
		{
			dat.max = dat.arr[low];
			dat.min = dat.arr[high];			
		}
	}
	else
	{
		int mid = (low + high)/2;	//divide array
		dat = MaxMin(low, mid, dat);
		data d1;
		d1 = dat;
		d1 = MaxMin(mid+1, high, d1);
		if(dat.max < d1.max)
			dat.max = d1.max;

		if(dat.min > d1.min)
			dat.min = d1.min;
	}

	return dat;
}

int main()
{
	int n, max, min, i, high, low;
	data dat;
	cout<<"\nEnter number of elements for the array : ";
	cin>>n;
	
	dat.arr = new int[n];

	for(i=0;i<n;i++)
	{
		cout<<"\nEnter element ["<<i+1<<"] : ";
		cin>>dat.arr[i];
	}

	dat.max = dat.arr[0];
	dat.min = dat.arr[0];
	dat = MaxMin(0,n-1,dat);

	cout<<"\nMax = "<<dat.max<<"\nMin = "<<dat.min<<endl;
}

/*
OUTPUT
Enter number of elements for the array : 7
Enter element [1] : 2
Enter element [2] : 9
Enter element [3] : 1
Enter element [4] : 6
Enter element [5] : 33
Enter element [6] : 90
Enter element [7] : 4
Max = 90
Min = 1
*/