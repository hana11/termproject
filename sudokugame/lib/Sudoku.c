#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>


int sudoku[10][10]={0,}, t_sudoku[10][10], ans, life, zero_cnt;
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
log input_log[81];
void get_sudoku(int _level)
{
	int i, j, k=1;
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
				zero_cnt++;
			}
		}
	}
	fclose(fp);
	life = zero_cnt-(_level+1)*7;
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
	printf("remain blank : %d\n", zero_cnt); 
	printf("remain life : %d\n", life); 
}
bool check_sudoku(int x, int y, int value) //coordinate, value
{
	int i, j;
	int tx, ty;
	for(i=0; i<9; i++)
	{
		if(sudoku[x][i]==value || sudoku[i][y]==value)
			return false;
	}
	tx = x/3;
	ty = y/3;

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
	int x, y, value, i, j, input_cnt;
	bool ch;

	input_cnt=0;
	zero_cnt=0;

	get_sudoku(level);

	while(1)
	{
		if(zero_cnt<1 || life==0)
		{	
			printf("End...\n");
			return;
		}
		
		printf("if value is -1, undo 1 step and  99 is giveup\n");
		printf("enter values (x, y, value) :");
		scanf("%d %d %d", &x, &y, &value);
		getchar();
		ch=0;
		if(value<0)
		{
			if(input_cnt>0)
			{
				printf("Undo 1 step\n");
				undo_sudoku(input_log[input_cnt].x, input_log[input_cnt--].y);
				zero_cnt++;
			}
			else
				printf("cannot undo. re-enter values\n");
			show_sudoku();
		}
		else if(value == 99)
		{
			printf("You give up the game.\n");
			return ;
		}
		else
		{
			if(sudoku[x][y]!=0)
				printf("cannot be inserted, re-enter values\n");
			else
			{
				for(i=0; i<9; i++) {
					if(check_sudoku(x, y, i+1))
					{
						ch=1;
					}
				}
				if(ch)
				{
					if(check_sudoku(x, y, value))
					{
						sudoku[x][y]=value;
						zero_cnt--;						
						show_sudoku();
						input_log[++input_cnt].x = x;
						input_log[input_cnt].y = y;
						
					}
					else
					{
						printf("wrong number!!\n");
						life--;
					}
				}
				else
				{
					printf("There is no value that satisfies the condition.\n");
					show_sudoku();
				}
			}
		}
	}

}
