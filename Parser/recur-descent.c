#include<stdio.h>

/*
	S->TL
	L->+S\E
	T->UM
	M->*T\E
	U->(S)\V
	V->0\1\2\3\4\5\6\7\8\9
*/

void S();
void L();
void T();
void M();
void U();
void V();

char input[20];
int count=0,error,i=0;
int main()
{
	int check=0;
	
	
	printf("ENTER STRING");
	scanf("%s",input);

	S();
	
	if(i==strlen(input)  && error==0)
		printf("STRING IS ACCEPTED");
		
	else
		printf("STRING IS REJECTED");
	
	return 0;
}


void V()
{
	if(input[i]>=48 && input[i]<=57)
	{
		i++;
	}
	else
	error=1;
}

void U()
{
	if(input[i]=='(')
	{
		i++;
		S();	
		if(input[i]==')')
		i++;
		else
		error=1;
	}
	else
	{
		V();
	}	
}

void S()
{
	T();
	L();
}

void L()
{
	if(input[i]=='+')
	{
		i++;
		S();
	}	
}

void T()
{
	U();
	M();
}

void M()
{
	if(input[i]=='*')
	{
		i++;
		T();
	}
}





