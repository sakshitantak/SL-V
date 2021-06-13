#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <ctype.h>

typedef struct mnemonicCodeTable{
char opcode[10];
int code;	//includes class and machine code in the form IS01
char class[3];
int operandCount;
}mot;

typedef struct pseudoOpcodeTable{
char opcode[10];
int code;		//includes intermediate code in the form DL01
char class[3];
int operandCount;
}pot;

typedef struct symbolTable{
int code;
char symbol[3];
int address;
int length;
}symtab;

typedef struct literalTable{
int code;
char literal[3];
int address;
}littab;

typedef struct registers{
char reg[10];
int code;
}reg;

void initMot(mot M[]);
void initPot(pot P[]);
void initPoolTab(int P[]);
void initSymTab(symtab S[]);
void initLitTab(littab L[]);
void initRegisters(reg R[], int* rc);

void makeTables(mot M[], pot P[]);

void displayMot(mot M[]);
void displayPot(pot P[]);
void displaySymTab(symtab S[], int stp);
void displayLitTab(littab L[], int ltp);
void displayPoolTab(int P[], int ptp);

int searchPot(pot P[], char str[]);
int searchMot(mot M[], char str[]);
int searchLitTab(littab L[], char str[], int ltp);
int searchSymTab(symtab S[], char str[], int stp);

int isLabel(int index, char str[], mot M[], pot P[]);
int isOperand(char str[], int wc, int index);
int isLiteral(char str[]);
int isRegister(reg R[], int rc, char str[]);

int addSymbol(symtab S[], char str[], int stp, int lc);
int addLiteral(littab L[], char str[], int ltp);
int originLCoperation(char op1[], char op2[], char operator, symtab S[], int stp);

void initMot(mot M[])
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		strcpy(M[i].opcode,"xxx");
		M[i].code = -1;
		strcpy(M[i].class,"xx");
		M[i].operandCount = -1;
	}
}

void initPot(pot P[])
{
	int i = 0;
	for(i=0;i<26;i++)
	{
		strcpy(P[i].opcode,"xxx");
		P[i].code = -1;
		strcpy(P[i].class,"xx");
		P[i].operandCount = -1;
		
	}
}

void initPoolTab(int P[])
{
	P[0] = 1;
}

void initSymTab(symtab S[])
{
	int i = 0;
	for(i=0;i<50;i++)
	{
		S[i].code = -1;
		strcpy(S[0].symbol,"$$");
		S[i].address = -1;
		S[i].length = -1;
	}
}

void initLitTab(littab L[])
{
	int i = 0;
	for(i=0;i<50;i++)
	{
		L[i].code = -1;
		strcpy(L[i].literal,"$$");
		L[i].address = -1;
	}
}

void initRegisters(reg R[], int* rc)
{
	int i = 0;
	
	strcpy(R[0].reg, "AREG");
	R[0].code = 0;
	
	strcpy(R[1].reg, "BREG");
	R[1].code = 1;
	
	strcpy(R[2].reg, "CREG");
	R[2].code = 2;
	
	strcpy(R[3].reg, "DREG");
	R[3].code = 3;
	
	*rc = 3; 

}

void makeTables(mot M[], pot P[])
{
	strcpy(M[0].opcode,"ADD");
	M[0].code = 01;
	strcpy(M[0].class,"IS");
	M[0].operandCount = 2;
	
	strcpy(M[1].opcode,"BC");
	M[1].code = 7;
	strcpy(M[1].class,"IS");
	M[1].operandCount = 1;
	
	strcpy(M[2].opcode,"CMP");
	M[2].code = 6;
	strcpy(M[2].class,"IS");
	M[2].operandCount = 2;
	
	strcpy(M[3].opcode,"DIV");
	M[3].code = 8;
	strcpy(M[3].class,"IS");
	M[3].operandCount = 2;
	
	strcpy(M[4].opcode,"DC");
	M[4].code = 1;
	strcpy(M[4].class,"DL");
	M[4].operandCount = 1;
	
	strcpy(M[5].opcode,"DS");
	M[5].code = 6;
	strcpy(M[5].class,"DL");
	M[5].operandCount = 1;
	
	strcpy(M[12].opcode,"MULT");
	M[12].code = 3;
	strcpy(M[12].class,"IS");
	M[12].operandCount = 2;
	
	strcpy(M[13].opcode,"MOVER");
	M[13].code = 4;
	strcpy(M[2].class,"IS");
	M[13].operandCount = 2;
	
	strcpy(M[14].opcode,"MOVEM");
	M[14].code = 5;
	strcpy(M[14].class,"IS");
	M[14].operandCount = 2;
	
	strcpy(M[15].opcode,"PRINT");
	M[15].code = 10;
	strcpy(M[15].class,"IS");
	M[15].operandCount = 1;
	
	strcpy(M[17].opcode,"READ");
	M[17].code = 9;
	strcpy(M[17].class,"IS");
	M[17].operandCount = 1;

	strcpy(M[18].opcode,"STOP");
	M[18].code = 0;
	strcpy(M[18].class,"IS");
	M[18].operandCount = 0;
	
	strcpy(M[19].opcode,"SUB");
	M[19].code = 2;
	strcpy(M[19].class,"IS");
	M[19].operandCount = 2;

	strcpy(P[4].opcode,"END");
	P[4].code = 2;
	strcpy(P[4].class,"AD");
	P[4].operandCount = 0;
	
	strcpy(P[5].opcode,"EQU");
	P[5].code = 1;
	strcpy(P[5].class,"AD");
	P[5].operandCount = 1;
	
	strcpy(P[11].opcode,"LTORG");
	P[11].code = 3;
	strcpy(P[11].class,"AD");
	P[11].operandCount = 0;
	
	strcpy(P[14].opcode,"ORIGIN");
	P[14].code = 4;
	strcpy(P[14].class,"AD");
	P[14].operandCount = 1;
	
	strcpy(P[18].opcode,"START");
	P[18].code = 1;
	strcpy(P[18].class,"AD");
	P[18].operandCount = 1;
}

void displayMot(mot M[])
{
	int i = 0;
	printf("\nMACHINE OPCODE TABLE\n");
	printf("\n--------------------------------------------------------");
	printf("\nMNEMONIC\tMACHINE\t\tCLASS\t\tOPERAND");
	printf("\nCODE\t\tCODE\t\tCOUNT");
	printf("\n--------------------------------------------------------");
	printf("\n");
	
	for(i=0;i<26;i++)
	{
		printf("\n%s\t\t%d\t\t%s\t\t%d",M[i].opcode,M[i].code,M[i].class,M[i].operandCount);
	}
	
	printf("\n--------------------------------------------------------");
	
}

void displayPot(pot P[])
{
	int i = 0;
	printf("\n\nPSEUDO OPCODE TABLE\n");
	printf("\n--------------------------------------------------------");
	printf("\nMNEMONIC\tINTERMEDIATE\tCLASS\t\tOPERAND");
	printf("\nCODE\t\tCODE\t\t\t\tCOUNT");
	printf("\n--------------------------------------------------------");
	printf("\n");
	for(i=0;i<26;i++)
	{
		printf("\n%s\t\t%d\t\t%s\t\t%d",P[i].opcode,P[i].code,P[i].class,P[i].operandCount);
	}
	printf("\n--------------------------------------------------------");
}

void displaySymTab(symtab S[], int stp)
{
	int i = 0;
	printf("\n\nSYMBOL TABLE");
	printf("\n---------------------------------");
	printf("\nCODE\tSYMBOL\tADDRESS\tLENGTH");
	printf("\n---------------------------------");
	
	for(i=0;i<stp;i++)
		printf("\n%d\t%s\t%d\t%d",S[i].code, S[i].symbol, S[i].address, S[i].length);
	
	printf("\n---------------------------------");
}

void displayLitTab(littab L[], int ltp)
{
	int i = 0;
	printf("\n\nLITERAL TABLE");
	printf("\n----------------------------------");
	printf("\nCODE\tLITERAL\tADDRESS");
	printf("\n----------------------------------");

	for(i=0;i<ltp;i++)
		printf("\n%d\t%s\t%d",L[i].code, L[i].literal, L[i].address);
	
	printf("\n---------------------------------");
}

void displayPoolTab(int P[], int ptp)
{
	int i = 0;
	printf("\n\nPOOL TABLE");
	printf("\n----------------------------------");
	printf("\nPOOL");
	printf("\n----------------------------------");

	for(i=0;i<ptp;i++)
		printf("\n%d",P[i]);

	printf("\n---------------------------------");
}

int searchPot(pot P[], char str[])
{
	int i;
	for(i=0;i<26;i++)
	{
		if((strcmp(P[i].opcode, str)) == 0)
			return i;
	}
	
	return -1;
}

int searchMot(mot M[], char str[])
{
	int i;
	
	for(i=0;i<26;i++)
	{
		if((strcmp(M[i].opcode, str)) == 0)
			return i;
	}
	
	return -1;
}

int searchLitTab(littab L[], char str[], int ltp)
{
	int i;
	for(i=0;i<ltp;i++)
		if((strcmp(L[i].literal, str)) == 0)
			return i;
	return -1;
}

int searchSymTab(symtab S[], char str[], int stp)
{
	int i;
	i = 0;
	printf("\nSearching %s in symbol table",str);
	for(i=0;i<stp;i++)
	{
		if((strcmp(S[i].symbol, str)) == 0)
			return i;
	}

	return -1;
}


int isLabel(int index, char str[], mot M[], pot P[])
{
	int flagMot = 0;
	int flagPot = 0;
	
	flagMot = searchMot(M, str);
	flagPot = searchPot(P, str);
	printf("\nChecking %s as label.",str);
	if(index == 0 && flagMot == -1 && flagPot == -1)
	{
		printf("\nfor %s...index = %d\nflagMot = %d\nflagpot = %d",str, index, flagMot, flagPot);
		return 1;
	}
	return -1;
}

int isOperand(char str[], int wc, int index)
{	
	printf("\nChecking %s as operand",str);
	if(wc == 3 && (index == 1 || index == 2))
		return 1;
	if(wc == 4 && (index == 2 || index == 3))
		return 1;
	return -1;
}

int isLiteral(char str[])
{
	printf("\nChecking is %s is a literal.");
	
	if(str[0] == '=')
		return 1;
	return -1;	
}

int isRegister(reg R[], int rc, char str[])
{
	int i = 0;
	for(i=0;i<=rc;i++)
		if((strcmp(R[i].reg, str)) == 0)
			return i;
	return -1;
}


int addSymbol(symtab S[], char str[], int stp, int lc)
{
	printf("\nAdding symbol %s to symbol table.",str);
	S[stp].code = stp;
	strcpy(S[stp].symbol, str);
	S[stp].address = lc;
	printf("\nS[stp].symbol : %s",S[stp].symbol);
	stp++;
	return stp;
}

int addLiteral(littab L[], char str[], int ltp)
{
	printf("\nAdding %s literal to literal table.",str);
	L[ltp].code = ltp;
	strcpy(L[ltp].literal, str);
	printf("\nL[ltp].literal : %s",L[ltp].literal);
	ltp++;
	return ltp;
}

int originLCoperation(char op1[], char op2[], char operator, symtab S[], int stp)
{
	int index;
	int lc = -1;
	
	if((index = searchSymTab(S, op1, stp)) != -1)
	{
		printf("\nop1 found in symbol table at location %d",index);
	
		switch(operator)
		{
			case '+':
				lc = S[index].address + atoi(op2);
				break;
				
			case '-':
				lc = S[index].address + atoi(op2);
				break;
			
			case '*':
				lc = S[index].address * atoi(op2);
				break;
			
			case '/':
				lc = S[index].address / atoi(op2);
				break;
		}
	}
	
	else
		printf("\nop1 doesn't exist in the symbol table.");
	
	return lc;
}

int imperativeArg(char str[])
{
	printf("\nChecking argument type of %s".,str);
	
}


int main()
{
	mot M[26];
	pot P[26];
	int pooltab[50];
	symtab S[50];
	littab L[50];
	reg R[4];
	int lc = 0;
	int ptp = 0;
	int ltp = 0;
	int stp = 0;
	int rc = 0;
	char buffer[500];
	char lineBuffer[500];
	char temp[50];
	char* tokens[4] = {NULL};
	//tokens = NULL;

	int i;
	int j;
	int index;
	int line = 0;
	int iter = 0;
	int wordCount[50] = {0};
	char op1[5];
	char op2[5];
	char operator;
	
	FILE* fex = NULL;
	FILE* trash = NULL;

	printf("\nInitialising MOT ...\n");
	initMot(M);
				
	printf("\nInitialising POT ...\n");
	initPot(P);

	printf("\nBuilding MOT and POT ...");
	makeTables(M,P);

	displayMot(M);
	displayPot(P);
	
	printf("\nInitialising symtab ...\n");
	initSymTab(S);
		
	printf("\nInitialising pooltab ...\n");
	initPoolTab(pooltab);
				
	printf("\nInitialising littab ...\n");
	initLitTab(L);
	
	printf("\nInitialising Registers ...\n");
	initRegisters(R, &rc);

	displaySymTab(S, stp);
	displayLitTab(L, stp);
	displayPoolTab(pooltab, ptp);

	fex = fopen("sampleProgram.txt", "r");
	
		
	if(fex == NULL)
		printf("\nError opening file!");

	else
	{
		line = 0;
		while(fgets(lineBuffer, 500, fex) != NULL)
		{
			//trash = fopen("trash", "a");
			iter = 0;
			printf("\nLine %d : %s",line,lineBuffer);
			tokens[iter] = strtok(lineBuffer, " ");
			//trim(tokens[iter], " ");
			printf("\nTokens for line %d : ",line);
					
			while(tokens[iter] != NULL)
			{
				//fprintf(trash,"%s\n",tokens[iter]);
				printf("[%s] ",tokens[iter]);
				iter++;
				tokens[iter] = strtok(NULL, " ");
			}
			iter = iter - 1;
			strcpy(buffer, tokens[iter]);
			strtok(buffer, "\n");
			buffer[strlen(buffer)+1] = '\0';
			strcpy(tokens[iter], buffer);
			iter+=1;
			
			wordCount[line] = iter;
			printf("\nWord count of line %d : %d", line, wordCount[line]);
			
			
				iter = 0;
				while(tokens[iter])
				{
					printf("\nProcessing token : %s",tokens[iter]);
					printf("\nLength of token : %ld",strlen(tokens[iter]));
					if((strcmp(tokens[iter], "START")) == 0)
					{
						index = searchPot(P, tokens[iter]);
						if(index == -1)
							printf("\n%s doesn't exist in POT.",tokens[iter]);
						else
						{
							printf("\n\n%s found in POT at index %d",tokens[iter], index);
							printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
							printf("\n%s\t%d\t%s\t%d",P[index].opcode, P[index].code, P[index].class, P[index].operandCount);
							printf("\n------------------------------------");
							iter++;
							lc = atoi(tokens[iter]);
							printf("\nLC initialised to : %d",lc);
						}
					}
					

					else if((strcmp(tokens[iter], "DC")) == 0)
					{
						index = searchMot(M, tokens[iter]);
						if(index == -1)
							printf("\n%s not found in MOT.",tokens[iter]);
						else
						{
							printf("\n%s found in MOT at index %d",tokens[iter], index);
							printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
							printf("\n%s\t%d\t%s\t%d",M[index].opcode, M[index].code, M[index].class, M[index].operandCount);
							printf("\n------------------------------------");
							lc+=1;
							printf("\nLC = %d",lc);
						} 
					}

					else if((strcmp(tokens[iter], "DS")) == 0)
					{
						index = searchMot(M, tokens[iter]);
						if(index == -1)
							printf("\n%s not found in MOT.",tokens[iter]);
						else
						{
							printf("\n%s is a declarative statement. Exists at location %d in MOT",tokens[iter], index);
							printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
							printf("\n%s\t%d\t%s\t%d",M[index].opcode, M[index].code, M[index].class, M[index].operandCount);
							printf("\n------------------------------------");
							iter++;
							lc+=atoi(tokens[iter]);
							index = searchSymTab(S, tokens[iter-2], stp);
							if(index == -1)
								printf("\n%s not found in symbol table.",tokens[iter-2]);
							else
							{
								printf("\n%s is a declarative statement. Exists at location %d in MOT",tokens[iter-2], index);
								S[index].length = atoi(tokens[iter]);
								displaySymTab(S, stp);
							}
							printf("\nLC = %d",lc);
						}
					}
					
					else if((strcmp("ORIGIN", tokens[iter])) == 0)
					{
						if((atoi(tokens[iter+1])) != 0)
						{
							//printf("\nIn if of ORIGIN");
							iter++;
							lc = atoi(tokens[iter]);
							printf("\nLC = %d",lc);
						}
						else
						{
							//printf("\nIn else of ORIGIN");
							printf("\ntokens[iter] : %s",tokens[iter]);
							//char temp[10];
							iter++;
							printf("\ntokens[iter] : %s",tokens[iter]);
							strcpy(temp, tokens[iter]);
							printf("\ntemp : %s",temp);
							
							i = 0;
							j = 0;
							
							while(temp[i] != '\0')
							{
								//printf("\nWhile to copy op1");
								if(temp[i] == '+' || temp[i] == '-' || temp[i] == '*' || temp[i] == '/')
								{
									operator = temp[i];	
									break;
								}
								
								op1[i] = temp[i];
								i++;
							}
							 op1[i] = '\0';
							 i++;
							
							while(temp[i] != '\0')
							{
								//printf("\nWhile to copy op2");
								op2[j] = temp[i];
								j++;
								i++;
							}
							
							op2[j] = '\0';
							
							printf("\nop1 : %s",op1);
							printf("\noperator : %c",operator);
							printf("\nop2 : %s",op2);
							
							int templc;
							templc = originLCoperation(op1, op2, operator, S, stp);
							if(templc != -1)
							{
								lc = templc;	
								printf("\nLC = %d",lc);
							}
						}
					}
					
					else if((index = searchMot(M, tokens[iter])) != -1)
					{
						printf("\n%s is an imperative statement. Exists at location %d in MOT.",tokens[iter], index);
						printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
						printf("\n%s\t%d\t%s\t%d",M[index].opcode, M[index].code, M[index].class, M[index].operandCount);
						printf("\n------------------------------------");
						if(wordCount[line]>1)
						{
							iter++;
							if((index = searchSymTab(S, tokens[iter], stp)) != -1)
							{
								printf("\nToken %s after %s is a symbol,",tokens[iter-1], tokens[iter]);
								printf("\n%s found in symbol table at location %d.",tokens[iter], index);
							}
							
							else if((index = isLiteral(tokens[iter])) != -1)
							{
								printf("%s after %s is a literal.", tokens[iter-1], tokens[iter]);
								
								if((index = searchLitTab(L, tokens[iter], ltp)) != -1)
									printf("\n%s found in literal table at location %d.",tokens[iter], index);
								else
								{
									printf("\n%s not found in literal table. Adding ...", tokens[iter]);
									ltp = addLiteral(L, tokens[iter], ltp);
								}
							}
							
							else if((index = isRegister(R, rc, tokens[iter])) != -1)
							{
								printf("\n%s is a register. Found in register table at location %d",tokens[iter], index);	
							}
							
							else if((index = searchSymTab(S, tokens[iter], stp)) == -1)
							{
								printf("\n%s after %s was not found in symbol table. Adding ...",tokens[iter-1], tokens[iter]);
								stp = addSymbol(S, tokens[iter], stp, lc);
								displaySymTab(S, stp);
							}
							
							
						}
						
						else
							printf("\nLine %d has only 1 imperative statement.",line);
					}


					else if((strcmp("END", tokens[iter])) == 0)
						printf("\nEND statement ecountered. Assembly finished!");

					else
					{
						if((isLabel(iter, tokens[iter], M, P)) == 1)
						{
							printf("\niter = %d",iter);
							printf("\n%s is a label.",tokens[iter]);
							index = searchSymTab(S, tokens[iter], stp);
							if(index == -1)
							{
								printf("\n%s not found in symbol table.",tokens[iter]);
								stp = addSymbol(S, tokens[iter], stp, lc);
								printf("\nstp = %d",stp);
								displaySymTab(S, stp);				
							}
							else
								printf("\n%s found in symbol table at %d location.",tokens[iter], index);
						}
						
						if(isOperand(tokens[iter], wordCount[line], iter) != -1)
							printf("\n%s is an operand", tokens[iter]);
							
						if((isLiteral(tokens[iter])) == 1)
						{
							printf("\niter = %d",iter);
							printf("\n%s is a literal.",tokens[iter]); 
							index = searchLitTab(L, tokens[iter], ltp);
							if(index == -1)
							{
								printf("\n%s not found in literal table.",tokens[iter]);
								ltp = addLiteral(L, tokens[iter], ltp);
								printf("\nltp = %d",ltp);
								displayLitTab(L, ltp);								
							}
							else
								printf("\n%s found in literal table at %d location.",tokens[iter], index);
						}
							
					}

					iter++;
				}
			
			
			line++;
			printf("\n==================================================================\n");


		}

	}

return 0;
}
