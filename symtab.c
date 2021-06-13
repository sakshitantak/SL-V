#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<ctype.h>

struct SYMTAB
{
	int srno;
	char opcode[10];
	int opCount;
}symtab;

struct SYMTAB T[7]={0,"start",1,1,"read",1,2,"print",1,3,"mover",2,4,"add",2,5,"sub",2,6,"stop",0};

int main()
{
	char buffer[200];
	char compare[10];
	int i = 0;
	int lcount = 1;
	int wcount = 0;
	int flag = 0;
	char c;
	
	FILE* fp = NULL;
	fp = fopen("sample.txt", "r");
	//fopen(fp);
	
	if(!fp)
	{
		printf("\n\nError : No such file exists!");
		return 0;
	}
	
	printf("\n\nThe file contents are : \n");
	while(fgets(buffer, sizeof(buffer), fp) != NULL)
	 {
	 	printf("%d\t",i);
	 	fputs(buffer, stdout);
	 	i++;
	 }
	 
	fclose(fp);
	
	printf("\n\n\tMNEMONIC TABLE\n");
	printf("---------------------------------");
	printf("\n|SR.NO\t OPCODE\t OPERAND SIZE   |\n");
	printf("---------------------------------");
	
	for(i=0;i<7;i++)
	{
		printf("\n|%d\t |%s\t |%d\t\t|",T[i].srno,T[i].opcode,T[i].opCount);	
	}
	
	printf("\n---------------------------------");
	
	fp = fopen("sample.txt", "r");
	
	if(!fp)
	{
		printf("\n\nError no such file exists!");
		return 0;
	}
	
	printf("\n\nScanning file...\n");
	
	
	
	while(c = fgetc(fp) != EOF)
	{
		wcount = 0;
		
		//c = fgetc(fp);

		printf("\n\n");
		
		while(c != '\n')
		{
			if(c == ' ')
				wcount++;
				
			printf("%c",c);
			c = fgetc(fp);
		}
		if(wcount)
			wcount++;
		
		printf("\nWord Count for line %d : %d", lcount, wcount);
		
		if(wcount == 1)
		{
			fscanf(fp,"%s",compare);
			flag = 0;
			i = 0;
			
			while(i<7)
			{
				if(strcmp(compare,T[i].opcode) == 0)
					flag = 1;
				i++;
			}
			
			if(!flag)
				printf("\nError at %d : %s not found in mnemonic table\n",lcount,compare);
		}
		
		else if(wcount == 2)
		{
			fscanf(fp,"%s %*s",compare);
			flag = 0;
			i = 0;
			
			while(i<7)
			{
				if(strcmp(compare,T[i].opcode) == 0)
					flag = 1;
				i++;
			}
			
			if(!flag)
				printf("\nError at %d : %s not found in mnemonic table\n",lcount,compare);
		}
		
		else if(wcount == 3)
		{
			fscanf(fp,"%s %*s %*s",compare);
			flag = 0;
			i = 0;
			
			while(i<7)
			{
				if(strcmp(compare,T[i].opcode) == 0)
					flag = 1;
				i++;
			}
			
			if(!flag)
				printf("\nError at %d : %s not found in mnemonic table\n",lcount,compare);
		}
		
		else
		{
			fscanf(fp,"%*s %s",compare);
			flag = 0;
			
			while(i<7)
			{
				if(strcmp(compare,T[i].opcode) == 0)
					flag = 1;
				i++;
			}
			
			if(!flag)
				printf("\nError at %d : %s not found in mnemonic table\n",lcount,compare);
		}
		/*fscanf(fp,"%s",compare);
		flag = 0;
		i = 0;
		
		while(i<7)
		{
			if((strcmp(compare,T[i].opcode)) == 0) 
				flag = 1;	//found in table
			i++;
		}
	
		if(!flag)
			printf("\nError at %d : %s not found in mnemonic table\n",lcount,compare);
		*/
		lcount++;
	}
	
	fclose(fp);
	
	return 0;

}
