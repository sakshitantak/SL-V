#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct terminalTable{
	char symbol[50];
	int index;
}terminal;

typedef struct identifierTable{
	char symbol[50];
	int index;
}identifier;

typedef struct literalTable{
	char symbol[50];
	int index;
}literal;

typedef struct universalSymbolTable{
	char symbol[50];
	char type[50];
	int index;
	int line;
}ust;

void displayTerminalTable(terminal T[], int n)
{
	int i = 0;
	printf("\nTERMINAL TABLE\nSYMBOL\tINDEX");

	for(i=0;i<n;i++)
	{
		printf("\n");
		printf("%s\t%d",T[i].symbol, T[i].index);
	}
}

int searchUnaryTerminal(terminal T[], int n, char c)
{
	int i = 0;
	for(i=0;i<n;i++)
		if(!strcmp(T[i].symbol, &c))
			return T[i].index;
	return -1;
}

void addUst(ust U[], int* uptr, char symb[], int i, char t[], int line)
{
	strcpy(U[*uptr].symbol, symb);
	strcpy(U[*uptr].type, t);
	U[*uptr].index = i;
	U[*uptr].line = line;
	*uptr+=1;
}

void displayUst(ust U[], int uptr)
{
	int i;
	printf("\nUNIVERSAL SYMBOL TABLE\nSYMBOL\t\tTYPE\tINDEX\tLINE");

	for(i=0;i<uptr;i++)
		printf("\n%s\t\t%s\t%d\t%d", U[i].symbol, U[i].type, U[i].index, U[i].line);
}

int searchLitTable(literal L[], int lptr, char c[])
{
	int i=0;
	for(i=0;i<lptr;i++)
		if(!strcmp(L[i].symbol, c))
			return L[i].index;
	return -1;
}

void addLiteral(literal L[], int *lptr, char c[])
{
	strcpy(L[*lptr].symbol, c);
	L[*lptr].index = *lptr; 
	*lptr+=1;
}

void displayLitTable(literal L[], int lptr)
{
	int i;
	printf("\nLITERAL TABLE\nLITERAL\t\tINDEX");

	for(i=0;i<lptr;i++)
		printf("\n%s\t\t%d",L[i].symbol, L[i].index);
}

void addIdentifier(identifier I[], int* idptr, char c[])
{
	strcpy(I[*idptr].symbol, c);
	I[*idptr].index = *idptr + 1;
	*idptr+=1;
}

int searchIdTable(identifier I[], int idptr, char c[])
{
	int i = 0;
	for(i=0;i<idptr;i++)
		if(!strcmp(I[i].symbol, c))
			return I[i].index;
	return -1;
}

void displayIdTable(identifier I[], int idptr)
{
	int i;
	printf("\nIDENTIFIER TABLE\nSYMBOL\tINDEX");
	for(i=0;i<idptr;i++)
		printf("\n%s\t%d", I[i].symbol, I[i].index);
}

int main()
{
	int i;
	int j;
	int k;
	int tnum;
	int line;
	
	int uptr;
	int lptr;
	int idptr;
	
	char buffer[500];
	char temp[500];
	char lit[500];
	char word[50] = {'\0'};
	char *	token[5];
	
	terminal T[32];
	ust U[500];
	literal L[500];
	identifier I[500];
	

	FILE* fin = NULL;
	FILE* fterm = NULL;
	FILE* fid = NULL;
	FILE* flit = NULL;
	FILE* fust = NULL;
	
	line = 0;
	uptr = 0;
	lptr = 0;
	idptr = 0;

	fin = fopen("sourceCode.txt", "r");
	fterm = fopen("terminals.txt", "r");

	printf("\nReading terminal table ..");

	if(fterm != NULL)
	{
		i = 0;
		while(fgets(buffer, 500, fterm) != NULL)
		{
			token[0] = strtok(buffer, " ");
			token[1] = strtok(NULL, " ");
			strtok(token[1], "\n");
			strcpy(temp, token[1]);
			temp[strlen(temp)+1] = '\0';
			strcpy(token[1], temp);
			strcpy(T[i].symbol, token[0]);
			T[i].index = atoi(token[1]);
			i++;
		}
		
		tnum = i;
		displayTerminalTable(T, tnum);
		printf("\n");

		if(fin != NULL)
		{
			line = 0;
			while(fgets(buffer, 500, fin))
			{
				printf("\nLine %d : %s",line,buffer);
				i = 0;
				j = 0;
				while(buffer[i] != '\0')
				{
					if(isspace(buffer[i]) == 0)
					{
						if((j = searchUnaryTerminal(T, tnum, buffer[i])) != -1 && buffer[i] != '"')
							addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
						
						if(buffer[i] == '=')
						{
							k = 0;
							if(isdigit(buffer[i+1]) != 0)
							{
								i++;
								while(isdigit(buffer[i]) != 0)
								{
									lit[k] = buffer[i];
									k++;
									i++;
								}
								
								i-=1;
								lit[k] = '\0';
								
								j = searchLitTable(L, lptr, lit);
								
								if(j != -1)
									addUst(U, &uptr, lit, L[j-1].index, "LIT", line);
								
								else
								{
									addLiteral(L, &lptr, lit);
									addUst(U, &uptr, L[lptr-1].symbol,L[lptr - 1].index, "LIT", line); 
								}
							}
						}
						
						if(buffer[i] == '"')
						{
							j = searchUnaryTerminal(T, tnum, buffer[i]);
							addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
							k = 0;
							i++;
							while(buffer[i] != '"')
							{
								lit[k] = buffer[i];
								k++;
								i++;
							}
							
							lit[k] = '\0';
							addLiteral(L, &lptr, lit);
							addUst(U, &uptr, L[lptr-1].symbol, L[lptr-1].index, "LIT", line);
							addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
						}
						
						if(isalpha(buffer[i]))
						{
							k = 0;
							while(isalnum(buffer[i]) || buffer[i] == '_')
							{
								temp[k] = buffer[i];
								k++;
								i++;
							}
							temp[k] = '\0';
							i--;
							
							j = searchIdTable(I, idptr, temp);
							
							if(j==-1)
							{
								addIdentifier(I, &idptr, temp);
								addUst(U, &uptr, I[idptr-1].symbol, I[idptr-1].index, "ID", line);	
							}
							
							else
								addUst(U, &uptr, I[j-1].symbol, I[j-1].index, "ID", line);
						}
					}
										
					i++;
				}
				line++;

			}
			displayUst(U, uptr);
			displayLitTable(L, lptr);
			displayIdTable(I, idptr);
		}
		
		else
		{
			printf("\nInput file could not be opened!");
			return 0;
		}
	}
	
	fid = fopen("identifiers.txt", "w");
	flit = fopen("literals.txt", "w");
	fust = fopen("UST.txt" ,"w");
	
	if(fid == NULL || flit == NULL || fust == NULL)
		printf("\nCouldn't open file successfully!");
	
	else
	{
		i = 0;
		while(i<idptr)
		{
			fprintf(fid, "%s %d\n", I[i].symbol, I[i].index); 
			i++;
		}
		
		i = 0;
		while(i<lptr)
		{
			fprintf(flit, "%s %d\n", L[i].symbol, L[i].index);
			i++;
		}
		
		i = 0;
		while(i<uptr)
		{
			fprintf(fust, "%s %d\n", U[i].symbol, U[i].index);
			i++;
		}
	}
	
	fclose(fterm);
	fclose(fin);
	fclose(flit);
	fclose(fid);
	fclose(fust);
	
	return 0;
}

/*OUTPUT
Reading terminal table ..
TERMINAL TABLE
SYMBOL	INDEX
(	1
)	2
{	3
}	4
+	5
-	6
/	7
*	8
,	9
;	10
"	11
>	12
<	13
&	14
|	15
^	16
!	17
int	18
float	19
double	20
char	21
void	22
for	23
while	24
include	25
[	27
]	28
'	29
#	30
%	31
=	32

Line 0 : main()

Line 1 : {

Line 2 : 	int a,b,c,d;

Line 3 : 	a=5;

Line 4 : 	b=10;

Line 5 : 	printf("Enter c : ");

Line 6 : 	scanf("%d",&c);

Line 7 : 	d=a+b;

Line 8 : 	printf("%d",d);

Line 9 : 	d=d+c;

Line 10 : 	printf("%d",c);

Line 11 : 	

Line 12 : }

UNIVERSAL SYMBOL TABLE
SYMBOL		TYPE	INDEX	LINE
main		ID	1	0
(		TRM	1	0
)		TRM	2	0
{		TRM	3	1
int		ID	2	2
a		ID	3	2
,		TRM	9	2
b		ID	4	2
,		TRM	9	2
c		ID	5	2
,		TRM	9	2
d		ID	6	2
;		TRM	10	2
a		ID	3	3
		TRM	0	3
5		LIT	0	3
;		TRM	10	3
b		ID	4	4
		TRM	0	4
10		LIT	1	4
;		TRM	10	4
printf		ID	7	5
(		TRM	1	5
"		TRM	11	5
Enter c : 		LIT	2	5
"		TRM	11	5
)		TRM	2	5
;		TRM	10	5
scanf		ID	8	6
(		TRM	1	6
"		TRM	11	6
%d		LIT	3	6
"		TRM	11	6
,		TRM	9	6
&		TRM	14	6
c		ID	5	6
)		TRM	2	6
;		TRM	10	6
d		ID	6	7
		TRM	0	7
a		ID	3	7
+		TRM	5	7
b		ID	4	7
;		TRM	10	7
printf		ID	7	8
(		TRM	1	8
"		TRM	11	8
%d		LIT	4	8
"		TRM	11	8
,		TRM	9	8
d		ID	6	8
)		TRM	2	8
;		TRM	10	8
d		ID	6	9
		TRM	0	9
d		ID	6	9
+		TRM	5	9
c		ID	5	9
;		TRM	10	9
printf		ID	7	10
(		TRM	1	10
"		TRM	11	10
%d		LIT	5	10
"		TRM	11	10
,		TRM	9	10
c		ID	5	10
)		TRM	2	10
;		TRM	10	10
}		TRM	4	12
LITERAL TABLE
LITERAL		INDEX
5		0
10		1
Enter c : 		2
%d		3
%d		4
%d		5
IDENTIFIER TABLE
SYMBOL	INDEX
main	1
int	2
a	3
b	4
c	5
d	6
printf	7
sakshi@sakshi-HP-Laptop-15-bs0xx:~/SP/LexicalAnalyser$ 
*/
