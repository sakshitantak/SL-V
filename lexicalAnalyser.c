#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int searchTerminal1(terminal T[], int n, char c)
{
	int i = 0;
	for(i=0;i<n;i++)
		if(!strcmp(T[i].symbol, &c))
			return T[i].index;
	return -1;
}

int searchTerminal2(terminal T[], int n, char c[])
{
	int i = 0;
	for(i=0;i<n;i++)
		if(!strcmp(T[i].symbol, c))
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
	printf("\nLITERAL TABLE\nLITERAL\t\t\tINDEX");

	for(i=0;i<lptr;i++)
		printf("\n%s\t\t\t%d",L[i].symbol, L[i].index);
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

int isOperator(char c, char c1)
{
	int flag = -1;
	switch(c)
	{
		case '+' :
			if(c1 == '+' || c1 == '=')
		  		flag = 1;
				
		break;
		
		case '-' :
			if(c1 == '-' || c1 == '=')
				flag = 1;
		break;
		
		case '*' :
			if(c1 == '=')
				flag = 1;
		break;
		
		case '/' :
			if(c1 == '=')
				flag = 1;
		break;
		
		case '=' :
			if(c1 == '=')
				flag = 1;
		break;
		
		case '<' :
			if(c1 == '=')
				flag = 1;
		break;
		
		case '>' :
			if(c1 == '=')
				flag = 1;
		break;
		
		case '&' :
			if(c1 == '&')
				flag = 1;
		break;
		
		case '|' :
			if(c1 == '|')
				flag = 1;
		break;
		
		
		default : 
			return flag;
	}
	
	return flag;
	
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
	char *token[2];
	char c;
	
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
						if(!isalnum(buffer[i]))
						{
							if(buffer[i] == '/' && buffer[i+1] == '/')
							{
								printf("\nSingle line comment found");
								while(buffer[i] != '\n')
									i++;
							}

							else if(isOperator(buffer[i], buffer[i+1]) == 1)
							{
								printf("\nOperator found : %c%c", buffer[i], buffer[i+1]);
								temp[0] = buffer[i];
								temp[1] = buffer[i+1];
								temp[2] = '\0';
								j = searchTerminal2(T, tnum, temp);
								if(j != -1)
								{
									printf("\nterminal %s found in TRM at location %d", T[j-1].symbol, T[j-1].index);
									addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
								}
								i+=2;
								continue;
							}
							
							else
							{
								if((j = searchTerminal1(T, tnum, buffer[i])) != -1 && buffer[i] != '"' && buffer[i] != '\'')
									addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
							
								if(j == -1)
								{
									printf("\nERROR : %c is not a valid token", buffer[i]);
									i++;
								}
							}
						}
						
						if(buffer[i] == '=' || buffer[i]  == '<' || buffer[i] == '>')
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
							j = searchTerminal1(T, tnum, buffer[i]);
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
							j = searchTerminal2(T, tnum, temp);
							if(j == -1)
							{
								j = searchIdTable(I, idptr, temp);	
								if(j==-1)
								{
									addIdentifier(I, &idptr, temp);
									addUst(U, &uptr, I[idptr-1].symbol, I[idptr-1].index, "ID", line);	
								}
							
								else
									addUst(U, &uptr, I[j-1].symbol, I[j-1].index, "ID", line);
							}
							
							else
								addUst(U, &uptr, T[j-1].symbol, T[j-1].index, "TRM", line);
								
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
