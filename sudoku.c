#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int sudoku[10][10];
void showSudoku()
{
	int q_sudoku[9][9]={0,};
	char buf[90];
        FILE *fp;
        int i,j,k=1;
        fp = fopen("ex1.txt","r");
        if(fp == NULL)
        {
                perror("FILE OPEN ERROR\n");
                exit(0);
        }

        fgets(buf,sizeof(buf),fp);
        fclose(fp);

	for(i=0; i<9; i++)
        {
                for(j=0; j<9; j++)
                {
                        k++;
                       	q_sudoku[i][j]=buf[k];
                        printf("%c",q_sudoku[i][j]);
                }
                printf("\n");
        }
}
bool check_sudoku(int x, int y, int value) //coordinate, value
{
	int i, j;
	int tx, ty;
	for(i=1; i<=9; i++)
	{
		if(sudoku[x][i]==value || sudoku[i][y]==value)
			return false;
	}
	tx = (x-1)/3;
	ty = (y-1)/3;

	for(i=tx*3; i<tx*3+3; i++) {
		for(j=ty*3; j<ty*3+3; j++) {
			if(sudoku[i][j]==value)
				return false;
		}
	}
	return true;
}
int main()
{
	int x, y,fd;
	while(1)
	{
		showsudoku();
		if(check_sudoku(x, y, value))
		{
			sudoku[x][y]=value;
		}
		else
		{
			printf("wrong number\n");
		}
	}
}
