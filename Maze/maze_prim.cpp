#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
#include<windows.h>
#include <cstddef>
#define N 31 //迷宫大小 
#define X0 1  
#define Y0 1	//点坐标 
#define BFLAG 2 //方块标记 

typedef enum {UP=1, DOWN, LEFT, RIGHT}Direction;

typedef struct block{
	int x;
	int y;
	Direction DIR;
	struct block *next;
}Block, *BList;

int block_sum = 0;
bool visited[N][N];
int maze[N][N]={0}; //0墙，1路 

void Init();
void print_maze();
void creat_maze();
BList chk_around(BList B, int x, int y);
BList chs_one(BList *B, int x, int y);
int chk_one(BList B, int *a);
void set_console_color(unsigned short color_index);
void cls();
void random_in_out(int x, int y);

int main()
{
	srand(time(0));
	Init();
	creat_maze();
	print_maze();
	puts("迷宫已生成！\n");
}

void Init()
{
	for(int i=1;i<N-1;i++)
	{
		for(int j=1;j<N-1;j++)
		{
			if(i%2!=0 && (i+j)%2==0)
			{
				maze[i][j]=1;
				visited[i][j]=false;
			}
		}
	}
}

void creat_maze()
{
	int ths_one[2];
	BList chs_B;
	BList pB = NULL;
	BList *ppB = &pB;
	int x = X0;
	int y = Y0;
	random_in_out(x, y);
	
	do{
		print_maze();
		cls();
		Sleep(1);
//		print_maze();
//		puts("\n");
 		pB = chk_around(pB, x, y);
//		BList f=pB;
//		while(f!=NULL)
//		{
//			printf("%d %d %d\n",f->x,f->y,f->DIR);
//			f = f->next;
//		}
//		print_maze();
//		puts("\n");
		again:
		chs_B = chs_one(ppB, x, y);
//		f=pB;
//		while(f!=NULL)
//		{
//			printf("%d %d %d\n",f->x,f->y,f->DIR);
//			f = f->next;
//		}
		//if(!chs_B) return;
		int chk_flag = chk_one(chs_B, ths_one);
		if(!block_sum) return ;
		if(!chk_flag) goto again;
		else
		{
			x = ths_one[0];
			y = ths_one[1];
		}
	}while(pB!=NULL);
}

void random_in_out(int x, int y)
{
	int chs_edge1=rand()%2; //选入口边 
	int chs_edge2;
	for(chs_edge2=0;chs_edge2%2!=1;chs_edge2=rand()%N) //选入口 
	;
	int chs_edge3=rand()%2; //选出口边
	int chs_edge4;
	for(chs_edge4=0;chs_edge4%2!=1;chs_edge4=rand()%N) //选出口 
	;
	if(chs_edge1 == 0)
	{
		maze[chs_edge2][0]=1;
		x=chs_edge2;
		y=1; 
	}
	if(chs_edge1 ==1)
	{
		maze[0][chs_edge2]=1;
		x=1;
		y=chs_edge2;
	}
	if(chs_edge3 ==0)
	maze[chs_edge4][N-1]=1;
	if(chs_edge3 ==1)
	maze[N-1][chs_edge4]=1;
}

int chk_one(BList B, int *a)
{
	int x=B->x ,y=B->y;
	if(B->DIR == UP)
	{
		if(visited[x-1][y])
		{
			maze[x][y] = 0;
			return 0;
		}
		maze[x][y] = 1;
		visited[x-1][y] = true;
		x = x-1;
	}
	else if(B->DIR == DOWN)
	{
		if(visited[x+1][y])
		{
			maze[x][y] = 0;
			return 0;
		}
		maze[x][y] = 1;
		visited[x+1][y] = true;
		x = x+1;
	}
	else if(B->DIR == LEFT)
	{
		if(visited[x][y-1])
		{
			maze[x][y] = 0;
			return 0;
		}
		maze[x][y] = 1;
		visited[x][y-1] = true;
		y = y-1;
	}
	else if(B->DIR == RIGHT)
	{
		if(visited[x][y+1])
		{
			maze[x][y] = 0;
			return 0;
		}
		maze[x][y] = 1;
		visited[x][y+1] = true;
		y = y+1;
	}
	
	a[0] = x;
	a[1] = y;
	return 1;
}

BList chs_one(BList *pB, int x, int y)
{
	//if(!block_sum) return 0;
	BList b;
	BList p = *pB;
	int rand_num = rand()%block_sum;
	if(!rand_num)
	{
		b = *pB;
		*pB = (*pB)->next;
	}
	else
	{
		while(--rand_num) p = p->next;
		b = p->next;
		p->next = p->next->next;
	}
	block_sum--;
	return b;
}

BList chk_around(BList B, int x, int y)
{
	BList p;
	
	if((x-1)>0) //上 
	{
		if(!maze[x-1][y])
		{
			maze[x-1][y] = BFLAG;
			p = (BList)malloc(sizeof(Block));
			p->DIR = UP;
			p->x = x-1;
			p->y = y;
			p->next = B;
			B = p;
			block_sum++;
		}
	}
	if((x+1)<N-1) //下 
	{
		if(!maze[x+1][y])
		{
			maze[x+1][y] = BFLAG;
			p = (BList)malloc(sizeof(Block));
			p->DIR = DOWN;
			p->x = x+1;
			p->y = y;
			p->next = B;
			B = p;
			block_sum++;
		}
	}
	if((y-1)>0) //左 
	{
		if(!maze[x][y-1])
		{
			maze[x][y-1] = BFLAG;
			p = (BList)malloc(sizeof(Block));
			p->DIR = LEFT;
			p->x = x;
			p->y = y-1;
			p->next = B;
			B = p;
			block_sum++;
		}
	}
	if((y+1)<N-1) //右 
	{
		if(!maze[x][y+1])
		{
			maze[x][y+1] = BFLAG;
			p = (BList)malloc(sizeof(Block));
			p->DIR = RIGHT;
			p->x = x;
			p->y = y+1;
			p->next = B;
			B = p;
			block_sum++;
		}
	}
	return B;
}


void cls()
{
    COORD coor={0,0};    //这是Windows API的结构体，用来存储光标位置
     // coor.X=i;                            
     // coor.Y=0 ;            
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
             //这三行代码将光标位置设为每一行的开头
      for(int j=0;j<2*N;j++)
      {
      	printf(" ");
	  }
	  printf("\n");
}

void print_maze()
{
	for(int m=0;m<N;m++)
	{
		for(int n=0;n<N;n++)
		{
//			if(maze[m][n] == 0)
//			{
//				printf("■");
//			}	
//			else
//			{
//				printf("  ");
//			}
			if(maze[m][n] == 0)
			{
				set_console_color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
				printf("■");
			}
		//	printf("0");
			else if(maze[m][n] == 1)
			{
				set_console_color(FOREGROUND_RED);
				printf("■");
			}
			else if(maze[m][n] == 2)
			{
				set_console_color(FOREGROUND_BLUE);
				printf("■");
			}
		//	printf("1");
		}
		puts("");
	}
}

void set_console_color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}
