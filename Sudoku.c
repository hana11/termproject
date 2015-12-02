#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
int sudoku[10][10]={0,}, t_sudoku[10][10], ans, life;
void start_sudoku();
void show_sudoku();
void get_sudoku();
bool check_sudoku(int x, int y, int value);
void undo_sudoku(int undo_x, int undo_y);
typedef struct _log
{
	int x;
	int y;
}log;
void get_sudoku()
{
	int i, j, k=1;
	char buf[90];
	FILE *fp;

	printf("Select Sudoku- Easy : 1,2  Medium : 3,4  Hard : 5,6  Stop : 999 \n");
	scanf("%d", &ans);
	life = 30-(ans+1)/2*5;
	fp = fopen("ex2.txt","r");

	if(fp == NULL)
	{
		perror("FILE OPEN ERROR\n");
		exit(0);
	}
	if(ans ==999)
	{
		return;
	}
	for(i=0; i< ans; i++)
	{
		fgets(buf,sizeof(buf),fp);
	}
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			k++;
			sudoku[i][j]=buf[k]-48;
			t_sudoku[i][j]=sudoku[i][j];
		}
	}
	fclose(fp);
	printf("------ You choose '%d' Question ------\n",ans);
	show_sudoku();
}
void show_sudoku()
{
	int i, j;
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			printf("%3d",sudoku[i][j]);
		}
		printf("\n");
	}
	printf("remain life : %d\n", life); 
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
void undo_sudoku(int undo_x, int undo_y)
{
	sudoku[undo_x][undo_y] = 0;
}
void start_sudoku()
{
	int x, y, value, i, input_cnt=0;
	bool ch;
	log input_log[81];
	get_sudoku();

	while(1)
	{
		/*************************************

		클라이언트로부터 x, y, value 값 받아옴

		**************************************/
		printf("if value is -1, undo 1 step\n");
		printf("enter values (x, y, value) :");
		scanf("%d %d %d", &x, &y, &value);
		//만족하는 값이 하나라도 있어야 함
		ch=0;
		if(value==-1)
		{
			if(input_cnt>0)
				undo_sudoku(input_log[--input_cnt].x, input_log[input_cnt].y);
			else
				printf("cannot undo. re-enter values\n");
			show_sudoku();
		}
		else
		{
			if(sudoku[x][y]!=0)
				printf("cannot be inerted, re-enter values\n");
			else
			{
				for(i=0; i<9; i++) {
					if(check_sudoku(x, y, i))
					{
						ch=1;
					}
				}
				if(ch)
				{
					if(check_sudoku(x, y, value))
					{
						sudoku[x][y]=value;
						show_sudoku();
						input_log[input_cnt].x = x;
						input_log[input_cnt++].y = y;
					}
					else
					{
						printf("wrong number\n");
						life--;
					}
					printf("remain life : %d\n", life); 
				}
				else
				{
					printf("There is no value that satisfies the condition.\n");
					undo_sudoku(input_log[--input_cnt].x, input_log[--input_cnt].y);
					printf("Undo 1 step\n");
					show_sudoku();
				}
			}
		}
	}
}
