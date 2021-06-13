#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int A(char input[])
{
	if(input[2] == 'c')
	{
		if(input[3] == '\0' || input[3] == 'd')
			return 1;
	}
	
	return -1;
}

void start(char input[])
{
	int flag=0;
	if(input[0] == 'a' && input[1] == 'b')
	{
		flag = A(input);
		if(flag == -1)
		{
			printf("\nError! doesn't belong to the set of productions");
			return;
		}
	
		else
			printf("\n%s belongs to the rules of production", input);
	}
	
	else
		printf("\n%s doesn't belong to the rules of production", input);
}

int main()
{
	char input[100];
		
	printf("\nEnter input string : ");
	scanf("%s", input);
	
	printf("\nInput string to be checked : %s", input);
	start(input);
	
}

