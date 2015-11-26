#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int sudoku[9][9]={0,};
	char buf[90];
	FILE *fp;
	int i,j,k=1;
	fp = fopen("ex1.txt","r");
	if(fp == NULL)
	{
		printf("FILE OPEN ERROR\n");
		exit(0);
	}

	fgets(buf,sizeof(buf),fp);

	fclose(fp);


	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			k++;
			sudoku[i][j]=buf[k];
			printf("%c",sudoku[i][j]);
		}
		printf("\n");
	}

}
