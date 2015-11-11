#include<stdio.h>
int sudoku[11][11];
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
	int x, y;
	while()
	{
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
