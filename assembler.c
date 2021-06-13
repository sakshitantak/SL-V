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

void stringComp(char str1[], char str2[])
{
	int i;
	i = strcmp(str1,str2);
	printf("\n%d",i);
}

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

int isLabel(char str[], mot M[], pot P[])
{
	if((searchMot(M, str)) == -1 && (searchPot(P, str)) == -1)
		return 1;
}

int main()
{
	mot M[26];
	pot P[26];
	int pooltab[50];
	symtab S[50];
	littab L[50];
	int lc = 0;
	int ptp = 1;
	int ltp = 1;
	int stp = 1;
	int rc = 0;
	char buffer[500];
	char lineBuffer[500];
	char temp[10];
	
	int choice = 0;
	int i;
	int index;
	int line = 0;
	
	FILE* fex = NULL;
	
	do{
	
		printf("\n\n----------MENU----------");
		printf("\n1. Inititalise MOT and POT");
		printf("\n2. Make MOT and POT");
		printf("\n3. Display MOT");
		printf("\n4. Dispaly POT");
		printf("\n5. Initialise Symbol Table, Pool Table, Literal Table");
		printf("\n6. Display Symbol Table, Pool Table, Literal Table");
		printf("\n7. Parse Code");
		printf("\n-1.Exit");
		printf("\n------------------------");
		
		printf("\n\nEnter choice : ");
		scanf("%d",&choice);
		printf("\n");
		
		switch(choice)
		{
			case 1: //init mot and pot
				printf("\nInitialising MOT ...\n");
				initMot(M);
				
				printf("\nInitialising POT ...\n");
				initPot(P);
			break;
			
			case 2: //build mot and pot
				printf("\nBuilding MOT and POT ...");
				makeTables(M,P);
			break;
			
			case 3: //display mot
				displayMot(M);
			break;
			
			case 4: //display pot
				displayPot(P);
			break;
			
			case 5: //init symtab, pooltab, littab
				printf("\nInitialising symtab ...\n");
				initSymTab(S);
				
				printf("\nInitialising pooltab ...\n");
				initPoolTab(pooltab);
				
				printf("\nInitialising littab ...\n");
				initLitTab(L);
			break;
			
			case 6: //display symtab, pooltab, littab
				displaySymTab(S, stp);
				displayLitTab(L, stp);
				displayPoolTab(pooltab, ptp);
			break;

			case 7: //parse code
				fex = fopen("sampleProgram.txt", "r");
				
				if(fex == NULL)
					printf("\nError opening file!");
				
				else
				{
					i = 0;
					while((fscanf(fex, "%s", buffer)) != -1)
					{
						printf("\n\nWord read from file in %d th iteration : %s",i,buffer);
						strcpy(temp, strtok(buffer, " "));
						
						//printf("\n\nword count in line : %ld",strlen(fgets(lineBuffer, 500, fex))+1);
						
						if((isLabel(temp, M, P)) == 1)
							printf("\n\n%s is a label",temp);
						
						if((strcmp(temp, "START")) == 0)
						{
							
							index = searchPot(P, temp);
							
							if(index == -1)
								printf("\n%s doesn't exist in the POT",buffer);
							
							else{
								printf("\n\n%s found in POT at index %d",temp, index);
								printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
								printf("\n%s\t%d\t%s\t%d",P[index].opcode, P[index].code, P[index].class, P[index].operandCount);
								printf("\n");
								fscanf(fex, "%s", buffer);
								strcpy(temp, strtok(buffer, " "));
								lc = atoi(temp);
								printf("\nLC initialised to : %d",lc);
							}
						}
						
						
						
						/*if((strcmp(temp, "DC")) == 0)
						{
							index = searchMot(M, temp);
							
							if(index == -1)
								printf("\n%s doesn't exist in the MOT",temp);
								
							else
							{
								printf("\n%s found in MOT at index %d",temp, index);
								printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
								printf("\n%s\t%d\t%s\t%d",M[index].opcode, M[index].code, M[index].class, M[index].operandCount);
								printf("\n");
								fscanf(fex, "%s", buffer);
								strcpy(temp, strtok(buffer, " "));
								if((strcmp(temp[0], "'")) == 0 && (strcmp(temp[2], "'")) == 0)
									lc+=1;
									printf("\nLC = %d",lc);
								
							}
						}*/
						
						
						
						if((strcmp(temp, "DS")) == 0)
						{
							index = searchMot(M, temp);
							
							if(index == -1)
								printf("\n\n%s doesn't exist in POT",temp);
								
							else
							{
								printf("\n\n%s found in MOT at index %d",temp, index);
								printf("\n\nOPCODE\tCODE\tCLASS\tOPERAND COUNT");
								printf("\n%s\t%d\t%s\t%d",M[index].opcode, M[index].code, M[index].class, M[index].operandCount);
								printf("\n");
								fscanf(fex, "%s", buffer);
								strcpy(temp, strtok(buffer, " "));
								lc+=atoi(temp);
								printf("\nLC = %d",lc);
							}
						}
						
						if((strcmp(temp, "END")) == 0)
						{
							printf("\n\nEND statement countered. File will be closed!");
							fclose(fex);
							break;
						}
						
						i++;
					}	
				}
			break;
			
			case -1: //exit
				//printTest();
				printf("\nThankyou for visiting");
			break;
			
			default: //default case
				printf("\nPlease make a valid choice from the menu");
			break;
			
		}
	}while(choice != -1);
	

	
return 0;
}

