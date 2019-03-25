#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<malloc.h>
#include<windows.h>
#include<dos.h>
#include<wincon.h>
#define N 31 //迷宫大小 
#define X0 1  
#define Y0 1	//起点坐标 
#define STACK_SIZE 200
#define STACK_INC 10

typedef struct{
	int x;
	int y;
}Block;

typedef struct{
	Block *sp;
	Block *bp;
	int stacksize;
}Stack;

bool visited[N][N];
int maze[N][N]={0}; //0墙，1路 

void Init();
void print_maze();
void init_Stack(Stack &s);
int chk_around(int x, int y);
void creat_maze();
void push(Stack &s, Block b);
void pop(Stack &s, Block &b);
bool isEmpty(Stack &s);
void cls();
void random_in_out(int x, int y);

int main()
{
	srand(time(0));
	Init();
	creat_maze();
	print_maze();
	printf("迷宫已生成！\n");
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
	Block b;
	Stack s;
	init_Stack(s);
	
	int chk_val;
	int x=X0;
	int y=Y0;
	
	random_in_out(x, y);
	visited[x][y]=1;
	do{
		print_maze();
		cls();
		Sleep(1);
		
		
		
		chk_val = chk_around(x,y);
		//	printf("%d\n",chk_val);
		if(chk_val!=-1)
		{
			
			b.x=x;
			b.y=y;
			push(s,b);
			
			if(chk_val==0)
			{
				x=x-2;
				maze[x+1][y]=1;
			}
			else if(chk_val==1)
			{
				x=x+2;
				maze[x-1][y]=1;
			}
			else if(chk_val==2)
			{
				y=y-2;
				maze[x][y+1]=1;
			}
			else if(chk_val==3)
			{
				y=y+2;
				maze[x][y-1]=1;
			}
			visited[x][y]=1;
		}
		else if(chk_val==-1)
		{
			pop(s,b);
			x=b.x;
			y=b.y;			
		}
		
		
	} while(!isEmpty(s));


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

int chk_around(int x, int y)
{
	int a[4]={0}; //up down left right
	int sum=0;
	//判断上下左右是否有未访问的点 
	if((x-2)>0)
	{
		if(!visited[x-2][y]) a[0]=1;
	}
	if((x+2)<N-1)
	{
		if(!visited[x+2][y]) a[1]=1;
	}
	if((y-2)>0)
	{
		if(!visited[x][y-2]) a[2]=1;
	}
	if((y+2)<N-1)
	{
		if(!visited[x][y+2]) a[3]=1;
	}
	//若无，则返回null 
	if(!(sum=a[0]+a[1]+a[2]+a[3])) return -1;
	//若有，则随机取一个点 
	int m[sum];
	for(int i=0,j=0;i<4;i++)
	{
		if(a[i]==1)
		{
			m[j]=i;
			j++;
		}
	}
//	printf("%d %d %d %d %d",a[0],a[1],a[2],a[3],c);
//	printf("%d %d",m[0],m[1]);
	int n=m[rand()%sum];
	return n; 
}

void init_Stack(Stack &s)
{
	s.bp = (Block*)malloc(STACK_SIZE * sizeof(Block));
	if(s.bp!=NULL)
	{
		s.sp=s.bp;
		s.stacksize=STACK_SIZE;
	}
	else
	{
		printf("栈分配失败!\n");
		exit(0);
	}
}

void push(Stack &s, Block b)
{
	if(s.sp-s.bp >= STACK_SIZE)
	{
		s.bp = (Block*)realloc(s.bp,(STACK_SIZE + STACK_INC)*sizeof(Block));
		if(s.bp == NULL) exit(0);
		s.stacksize += STACK_INC;
	}
	
	*s.sp = b;
	s.sp++;
}

void pop(Stack &s, Block &b)
{
	if(s.bp == s.sp)
		return;
	s.sp--;
	b = *s.sp;
}

bool isEmpty(Stack &s)
{
	if(s.sp == s.bp) return true;
	else return false;
}

void print_maze()
{
	for(int m=0;m<N;m++)
	{
		for(int n=0;n<N;n++)
		{
			if(maze[m][n] == 0)
			printf("■");
			else
			printf("  ");
		}
		puts("");
	}
}

