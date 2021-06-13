/*
Title : Write  a  program to  implement Pass-I of  Two-pass  assembler  for  Symbols  and Literal  processing  ( For hypothetical instruction 		set from Dhamdhere) considering following cases
	i.Forward references
	ii.DS and DC statement
	iii.START, EQU, LTORG, END.
	iv.Error handling: symbol used but not defined, invalid instruction/register etc.
Roll No. : 3022
Name : Dhonde Shivam

Sample Input :

-	START	500	-
-	MOVER	AREG	LAB
-	ADD	BREG	LOOP
L1	DS	20	-
-	LOAD	AREG	='5'
-	ADD	BREG	='1'
BACK	EQU	L1	-
L2	SUB	CREG	LAB
-	LTORG	-	-
-	MOVEM	AREG	LAB
-	ORIGIN	L2	-
-	SUB	DREG	='2'
LAB	DC	2	-
LOOP	DS	5	-
-	STOP	-	-
-	END	-	-

Sample Output :

0	(AD,1)	(C,500)
500	(IS,4)	(R,1)	(S,1)
501	(IS,1)	(R,2)	(S,2)
502	(DL,2)	(C,20)
522	(IS,11)	(R,1)	(L,1)
523	(IS,1)	(R,2)	(L,2)
524	(AD,5)	(S,3)
524	(IS,2)	(R,3)	(S,1)
527	(IS,5)	(R,1)	(S,1)
528	(AD,4)	(S,5)
524	(IS,2)	(R,4)	(L,3)
525	(DL,1)	(C,2)
526	(DL,2)	(C,5)
531	(IS,0)
532	(AD,2)

SYMBOL TABLE
1	LAB	525	2
2	LOOP	526	5
3	L1	502	20
4	BACK	502	-
5	L2	524	-

LITERAL TABLE
1	'5'	525
2	'1'	526
3	'2'	532

POOL TABLE
1	1
2	3

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

enum reg
{
	AREG=01,BREG,CREG,DREG
}r;

typedef struct instr
{
	char label[20];
	char instru[20];
	char arg1[20];
	char arg2[20];
}instr;

typedef struct symtab
{
	int sno;
	char sym[10];
	int add;
	char size[10];
}symtab;

typedef struct littab
{
	int sno;
	char lit[20];
	int add;
}littab;

typedef struct pooltab
{
	int sno;
	int pool;
}pooltab;

int main()
{
	FILE *fp_ex,*fp_ic,*fp_mot;
	int i,j,k,no_mot=1,s_chck,l_chck,count=0;
	char str[20];
	symtab s[20];
	int s_cnt=1;
	littab l[20];
	char *lit;
	int l_cnt=1;
	pooltab p[20];
	int p_cnt=1,flag,instru_flag=0;
	instr in;
	instr end_chck;
	int LC=0;
	char class_mc[20],regcode[20],slc[20];
	int pool_flag=0,ltorg_flag=0,lt=0,poolpt=1;
	int REG,lit_count=0,err_flag=0;
	char mot_instru[20],smot_class[20],mot_class[20],mot_size[20];
	int mot_mc,smot_mc,mconst,sym_err=0;

	k=0;
	int pool_cnt=1;

	p[k].sno=pool_cnt++;
	p[k].pool=1;
	k++;
	
	fp_ex=fopen("example1","r");
	fp_ic=fopen("ICode","w");
	fp_mot=fopen("mot_table","r");
	i=j=0;
	fscanf(fp_ex,"%s %s %s %s",in.label,in.instru,in.arg1,in.arg2);
	fseek(fp_ex,-10,SEEK_END);
	fscanf(fp_ex,"%s %s %s %s",end_chck.label,end_chck.instru,end_chck.arg1,end_chck.arg2);

	if(!strcmp(in.instru,"START") && !strcmp(end_chck.instru,"END"))
	{
		rewind(fp_ex);
		fscanf(fp_ex,"%s %s %s %s",in.label,in.instru,in.arg1,in.arg2);
		while(strcmp(in.instru,"END"))
		{
			s_chck=0;
			flag=1;
			
			while(!feof(fp_mot))
			{			
				fscanf(fp_mot,"%s %d %s %s",mot_instru,&mot_mc,mot_class,mot_size);
				if(!strcmp(in.instru,mot_instru))
				{
					strcpy(smot_class,mot_class);
					smot_mc=mot_mc;
					sym_err=1;
					break;
				}
				sym_err=0;
			}
			if(sym_err==0)
				break;
			rewind(fp_mot);

			if(strcmp(in.label,"-"))
			{
				while(s[s_chck].sno-1<i)
				{
					if(!strcmp(in.label,s[s_chck].sym))
					{
						flag=0;
						break;
					}
					else
					{
						flag=1;	
					}
					
					s_chck++;
				}
				if(flag==1)
				{
					s[i].sno=s_cnt++;
					strcpy(s[i].sym,in.label);
					s[i].add=LC;
					strcpy(s[i].size,"-");
					i++;
				}
			}
			int zz;
			for(zz=0;zz<i;zz++)
			{
				if(!strcmp(in.label,s[zz].sym))
				{
					s[zz].add=LC;
				}
			}
			flag=1;
			s_chck=0;
			if(isalpha(in.arg1[0]) && !(AREG || BREG || CREG || DREG))
			{
				while(s[s_chck].sno-1<i)
				{
					if(!strcmp(in.arg1,s[s_chck].sym))
					{
						flag=0;
						break;
					}
					else
					{
						flag=1;
						
					}
					
					s_chck++;
				}
				if(flag==1)
				{
					s[i].sno=s_cnt++;
					strcpy(s[i].sym,in.arg1);
					s[i].add=0;
					strcpy(s[i].size,"-");
					i++;
				}
			}
			flag=1;
			s_chck=0;
			if(isalpha(in.arg2[0]))
			{
				while(s[s_chck].sno-1<i)
				{
					if(!strcmp(in.arg2,s[s_chck].sym))
					{
						flag=0;
						break;
					}
					else
					{
						flag=1;	
					}
					
					s_chck++;
				}
				if(flag==1)
				{
					s[i].sno=s_cnt++;
					strcpy(s[i].sym,in.arg2);
					s[i].add=0;
					strcpy(s[i].size,"-");
					i++;
				}
			}
			
			flag=1;
			if(in.arg1[0]=='=')
			{
				lit=in.arg1+1;
				if(pool_flag==1)
				{
					while(l[l_chck].sno-1<j)
					{
						if(!strcmp(lit,l[l_chck].lit))
						{
							flag=0;
							break;
						}
						else
						{
							flag=1;	
						}
						
						l_chck++;
					}
					if(flag==1)
					{
						l[j].sno=l_cnt++;
						strcpy(l[j].lit,lit);
						l[j].add=0;
						j++;
						lit_count++;
					}
				}
				else
				{
					l_chck=0;
					while(l[l_chck].sno-1<j)
					{
						if(!strcmp(lit,l[l_chck].lit))
						{
							flag=0;
							break;
						}
						else
						{
							flag=1;	
						}
						
						l_chck++;
					}
					if(flag==1)
					{
						l[j].sno=l_cnt++;
						strcpy(l[j].lit,lit);
						l[j].add=0;
						j++;
						lit_count++;
					}
				}
			}
			
			flag=1;
			if(in.arg2[0]=='=')
			{
				lit=in.arg2+1;
				if(pool_flag==1)
				{
					while(l[l_chck].sno-1<j)
					{
						if(!strcmp(lit,l[l_chck].lit))
						{
							flag=0;
							break;
						}
						else
						{
							flag=1;	
						}
						
						l_chck++;
					}
					if(flag==1)
					{
						l[j].sno=l_cnt++;
						strcpy(l[j].lit,lit);
						l[j].add=0;
						j++;
						lit_count++;
					}
				}
				else
				{
					l_chck=0;
					while(l[l_chck].sno-1<j)
					{
						if(!strcmp(lit,l[l_chck].lit))
						{
							flag=0;
							break;
						}
						else
						{
							flag=1;	
						}
						
						l_chck++;
					}
					if(flag==1)
					{
						l[j].sno=l_cnt++;
						strcpy(l[j].lit,lit);
						l[j].add=0;
						j++;
						lit_count++;
					}
				}
			}

			if(!strcmp(in.instru,"LTORG") || !strcmp(in.instru,"END"))
			{
				int x,lc,lit_cnt;
				p[k].sno=pool_cnt++;
				p[k].pool=j+1;
				k++;
				l_chck=j+1;
				pool_flag=1;
				ltorg_flag=1;
				lc=LC;
				lit_cnt=lit_count;
				while(lit_count>0)
				{	
					l[lt++].add=lc++;
					lit_count--;
				}
				LC=LC+lit_cnt;
				lit_count=0;
				
			}
			if(ltorg_flag==1)
			{
				lt=p[poolpt++].pool-1;
				ltorg_flag=0;
			}
			
			if(strcmp(in.arg1,"-") && strcmp(in.arg2,"-"))
			{
				if(!strcmp(in.arg1,"AREG") || !strcmp(in.arg1,"BREG") || !strcmp(in.arg1,"CREG") || !strcmp(in.arg1,"DREG"))
				{
					if(!strcmp(in.arg1,"AREG"))
						REG=AREG;
					else if(!strcmp(in.arg1,"BREG"))
						REG=BREG;
					else if(!strcmp(in.arg1,"CREG"))
						REG=CREG;
					else
						REG=DREG;
	
					if(isdigit(in.arg2[0]))
					{
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(C,%d)\n",LC,smot_class,smot_mc,REG,atoi(in.arg2));
					}
					else if(isalpha(in.arg2[0]))
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.arg2,s[k].sym))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(S,%d)\n",LC,smot_class,smot_mc,REG,k+1);
					}
					else
					{
						int k;
						for(k=lt;k<j;k++)
						{
							if(!strcmp(in.arg2,l[k].lit))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(L,%d)\n",LC,smot_class,smot_mc,REG,k);
					}
				}
				
				else if(isdigit(in.arg1[0]))
				{
					if(isdigit(in.arg2[0]))
					{
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(C,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),atoi(in.arg2));
					}
					else if(isalpha(in.arg2[0]))
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.arg2,s[k].sym))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(S,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k+1);
					}
					else
					{
						int k;
						for(k=lt;k<j;k++)
						{
							if(!strcmp(in.arg2,l[k].lit))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(L,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k);
					}
				}
				else if(isalpha(in.arg1[0]))
				{
					if(isdigit(in.arg2[0]))
					{
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(C,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),atoi(in.arg2));
					}
					else if(isalpha(in.arg2[0]))
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.arg2,s[k].sym))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(S,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k+1);
					}
					else
					{
						int k;
						for(k=lt;k<j;k++)
						{
							if(!strcmp(in.arg2,l[k].lit))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(L,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k);
					}
				}
				else
				{
					if(isdigit(in.arg2[0]))
					{
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(C,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),atoi(in.arg2));
					}
					else if(isalpha(in.arg2[0]))
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.arg2,s[k].sym))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(S,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k+1);
					}
					else
					{
						int k;
						for(k=lt;k<j;k++)
						{
							if(!strcmp(in.arg2,l[k].lit))
							{
								break;
							}
						}
						fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\t(L,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1),k);
					}
				}
				if(!strcmp(smot_class,"IS"))
				{
					LC++;
				}
				else if(!strcmp(smot_class,"DL"))
				{
					if(smot_mc==1)
					{
						LC++;
					}
					else
					{
						LC=LC+atoi(in.arg1);
					}
				}
			}
			else if(strcmp(in.arg1,"-"))
			{
				if(!strcmp(in.arg1,"AREG") || !strcmp(in.arg1,"BREG") || !strcmp(in.arg1,"CREG") || !strcmp(in.arg1,"DREG"))
				{
					if(!strcmp(in.arg1,"AREG"))
						REG=AREG;
					else if(!strcmp(in.arg1,"BREG"))
						REG=BREG;
					else if(!strcmp(in.arg1,"CREG"))
						REG=CREG;
					else
						REG=DREG;
				
					fprintf(fp_ic,"%d\t(%s,%d)\t(R,%d)\n",LC,smot_class,smot_mc,REG);
				}
				else if(isdigit(in.arg1[0]))
				{
					if(!strcmp(in.instru,"EQU"))
					{
						int k=0;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.label,s[k].sym))
							{
								break;
							}
						}
						
						s[k].add=atoi(in.arg1);
					}
					fprintf(fp_ic,"%d\t(%s,%d)\t(C,%d)\n",LC,smot_class,smot_mc,atoi(in.arg1));
				}
				else if(isalpha(in.arg1[0]))
				{	
					int k,m=0,n=0;
					int j,l,flag=2;
					char sym[20];
					char no[20];

					for(j=0;j<strlen(in.arg1);j++)
					{
						if(in.arg1[j]=='+')
						{
							flag=1;
							break;
						}
						if(in.arg1[j]=='-')
						{
							flag=0;
							break;
						}
						sym[m++]=in.arg1[j];	
					}
					for(l=j+1;l<strlen(in.arg1);l++)
					{
						no[n++]=in.arg1[l];
					}
					sym[m]='\0';
					no[n]='\0';

					for(k=0;k<i;k++)
					{
						if(!strcmp(sym,s[k].sym))
						{
							break;
						}
					}
					
					if(!strcmp(in.instru,"EQU"))
					{
						int kk=0;
						for(kk=0;kk<i;kk++)
						{
							if(!strcmp(in.label,s[kk].sym))
							{
								break;
							}
						}
						if(flag==1)
						{
							s[kk].add=s[k].add+atoi(no);
							fprintf(fp_ic,"%d\t(%s,%d)\t(S,%d)+%d\n",LC,smot_class,smot_mc,k+1,atoi(no));
						}
						else if(flag==0)
						{
							s[kk].add=s[k].add-atoi(no);
							fprintf(fp_ic,"%d\t(%s,%d)\t(S,%d)-%d\n",LC,smot_class,smot_mc,k+1,atoi(no));
						}
						else
							s[kk].add=s[k].add;
					}
					if(flag!=1 && flag!=0)
						fprintf(fp_ic,"%d\t(%s,%d)\t(S,%d)\n",LC,smot_class,smot_mc,k+1);
				}
				else
				{	
					int k;
					for(k=lt;k<j;k++)
					{
						if(!strcmp(in.arg1,l[k].lit))
						{
							break;
						}
					}
					if(!strcmp(in.instru,"EQU"))
					{
						int kk=0;
						for(kk=0;kk<i;kk++)
						{
							if(!strcmp(in.label,s[kk].sym))
							{
								break;
							}
						}
						
						s[kk].add=l[k].add;
					}
					fprintf(fp_ic,"%d\t(%s,%d)\t(L,%d)\n",LC,smot_class,smot_mc,k+1);
				}
				
				if(!strcmp(in.instru,"START") || !strcmp(in.instru,"ORIGIN"))
				{
					if(isalpha(in.arg1[0]))
					{	
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.arg1,s[k].sym))
							{
								LC=s[k].add;
								break;
							}
						}	
					}
					else
						LC=atoi(in.arg1);	
				}
				else if(!strcmp(smot_class,"IS"))
				{
					LC++;
				}
				else if(!strcmp(smot_class,"DL"))
				{
					if(smot_mc==1)
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.label,s[k].sym))
							{
								break;
							}
						}
						s[k].add=LC;
						strcpy(s[k].size,in.arg1);
						LC++;
					}
					else
					{
						int k;
						for(k=0;k<i;k++)
						{
							if(!strcmp(in.label,s[k].sym))
							{
								break;
							}
						}
						s[k].add=LC;
						strcpy(s[k].size,in.arg1);
						LC=LC+atoi(in.arg1);
					}
				}
				
			}
			else
			{
				if(strcmp(in.instru,"LTORG"))
					fprintf(fp_ic,"%d\t(%s,%d)\n",LC,smot_class,smot_mc);
				
				if(!strcmp(smot_class,"IS"))
				{
					LC++;
				}
				else if(!strcmp(smot_class,"DL"))
				{
					if(smot_mc==1)
					{
						LC++;
					}
					else
					{
						LC=LC+atoi(in.arg1);
					}
				}
			}

			fscanf(fp_ex,"%s %s %s %s",in.label,in.instru,in.arg1,in.arg2);
		}
		int lc,x,lit_cnt;
		lc=LC;
		
		while(lit_count>0)
		{	
			l[lt++].add=lc++;
			lit_count--;
		}
		fprintf(fp_ic,"%d\t(AD,2)\n",LC);
		err_flag=1;
		if(sym_err==0)
		{
			printf("\nInvalid Instruction\n");
		}
	}
	else
	{
		printf("\nError\n");
	}
	if(err_flag==1 && sym_err==1)
	{
		printf("\nSYMBOL TABLE\n");
		for(count=0;count<i;count++)
		{
			printf("%d\t%s\t%d\t%s\n",s[count].sno,s[count].sym,s[count].add,s[count].size);
		}
		
		printf("\nLITERAL TABLE\n");
		for(count=0;count<j;count++)
		{
			printf("%d\t%s\t%d\n",l[count].sno,l[count].lit,l[count].add);
		}
		
		printf("\nPOOL TABLE\n");
		for(count=0;count<k;count++)
		{
			printf("%d\t%d\n",p[count].sno,p[count].pool);
		}
	}

	fclose(fp_ex);	
		
	return 0;
}
//END
