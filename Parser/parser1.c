//S -> abA
//A -> cd | c | e
//test cases : abc, abcd, vhbdf
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int V(char input[], int i)
{
	if(input[i] > 48 || input[i] < 57)
		return (i+1);
	return -1;
}

int U(char input[], int i)
{
	if(input[i] == '(')
	{
		i = start(input, i+1)
		if(i != -1)
		{
			if(input[i] == ')')
				return (i+1);
		}
	}
	
	else
	{
		i = V(input, i);
		return i;
	}
	
	return -1;	
}

int M(char input[], int i)
{
	if(input[i] == '*')
	{
		i = T(input, i+1);
		return i;		
	}
	
}



