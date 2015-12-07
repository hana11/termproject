#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>


int sudoku[10][10]={0,}, t_sudoku[10][10], ans, life;
void show_sudoku();
void get_sudoku();
bool check_sudoku(int x, int y, int value);
void undo_sudoku(int undo_x, int undo_y);
void start_sudoku();
typedef struct _log
{
	int x;
	int y;
}log;
void get_sudoku(int _level)
{
	int i, j, k=1, zero=0;
	char buf[90];
	FILE *fp;


	fp = fopen("ex2.txt","r");

	if(fp == NULL)
	{
		perror("FILE OPEN ERROR\n");
		exit(0);
	}
	if(_level ==999)
	{
		return;
	}
	for(i=0; i< _level; i++)
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
			if(t_sudoku[i][j]==0)
			{
				zero++;
			}
		}
	}
	fclose(fp);
	life = zero-(_level+1)*7;
	printf("------ You choose '%d' Question ------\n",_level);
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
void start_sudoku(int level)
{
	int x, y, value, i, j, input_cnt, zero_cnt;
	bool ch;
	log input_log[81];

	input_cnt=0;
	zero_cnt=0;

	get_sudoku(level);

	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if(sudoku[i][j]==0)
				zero_cnt++;
		}
	}
	while(1)
	{
		printf("if value is -1, undo 1 step and  99 is giveup\n");
		printf("enter values (x, y, value) :");
		scanf("%d %d %d", &x, &y, &value);
		ch=0;
		if(input_cnt==zero_cnt)
		{	
			break;
		}
		if(value==-1)
		{
			if(input_cnt>0)
				undo_sudoku(input_log[--input_cnt].x, input_log[input_cnt].y);
			else
				printf("cannot undo. re-enter values\n");
			show_sudoku();
		}
		if(value == 99)
		{
			printf("You give up the game.\n");
			return ;
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
