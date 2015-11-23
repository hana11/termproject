#include <stdio.h>
#include <stdlib.h>
char buf[90];
int sudoku[9][9]={0,};
void selectSudoku()
{
	int i,j,k=1;
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
int main(void)
{
	FILE *fp;
	int i,j,k=1;
	int ans =0;
 	while(1)
	{
		printf("Select Sudoku- Easy : 1,2 Medium : 3,4 Hard : 5 , 6 Stop : 999 \n");
        	scanf("%d",&ans);
		if(ans == 999)
		{
			break;
		}
		fp = fopen("ex1.txt","r");
		if(fp == NULL)
		{
			printf("FILE OPEN ERROR\n");
			exit(0);
		}
		for(i=0; i<ans; i++)
		{
			fgets(buf,sizeof(buf),fp);
		}
		fclose(fp);
		selectSudoku();
	}

}
