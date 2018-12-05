## 贪吃蛇 移动版和吃货版下载途径：


### 文件夹网页地址：

[c文件下载处](https://github.com/zzm99/homework/tree/gh-pages/tanchishe1)

### 代码展示：

#### snake.move.c
```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#define H 10//地图的高 
#define W 10//地图的宽
#define w 119
#define a 97
#define s 115
#define d 100
int i, j;//循环变量 
int sum = 5;//蛇的长度
int over = 0;//游戏结束标志（自吃或者碰墙）
int dx[4] = {0, 0, -1, 1}; //左右移动
int dy[4] = {-1, 1, 0, 0}; //上下移动

struct Snake{//蛇的每个结点的数据类型 
	int x, y;
	int now;//保存当前结点的方向，0、1、2、3分别为左右上下 
}Snake[H*W];

const char Shead = 'H';
const char Sbody = 'X';
const char Sfood = '$';
const char Snode = ' ';
const char Swall = '*';

void Initial();//地图的初始化
void Show(); //刷新显示地图 
void Move(); //蛇的移动
void Check_Border();//检查蛇头是否越界
void Check_Head(int x, int y); //检查蛇头移动后的情况

char GameMap[H][W];//游戏地图 

int main()
{
	srand(time(NULL)); 
	Initial();
	while(1)
	{
		int ch;
		ch = getchar();
		switch(ch){
			case a: Snake[0].now = 0,Move(); 
					break;				
			case d: Snake[0].now = 1,Move();
					break;
			case w:	Snake[0].now = 2,Move();
					break;
			case s:	Snake[0].now = 3,Move();
					break;
		}	
		if(over)  //自吃或碰墙即游戏结束  
  		{   
   			printf("\n**游戏结束**\n"); 
			printf("你的得分为：%d",sum); 
     		break;  
  		} 
  		system("cls");   //清空地图再显示刷新好的地图 
  		for(i = 0; i < H; i++)   
  		{   
   			for(j = 0; j < W; j++)  
    		printf("%c", GameMap[i][j]);  
   			printf("\n");  
  		}  
	}
	return 0;
 } 

void Initial()
{
	memset(GameMap, ' ', sizeof(GameMap));
	for(i=0; i<W; i++)
	{
		GameMap[0][i] = '*';
		GameMap[H-1][i] = '*';
	}
	for(i=0; i<H; i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W-1] = '*';
	}
	for(i=1; i<5; i++)
		GameMap[1][i] = 'X';
	GameMap[1][5] = 'H';
	Snake[0].x = 1; Snake[0].y = 5;
	Snake[0].now = -1;
	for(i=1; i<5; i++)
	{
		Snake[i].x = 1;
		Snake[i].y = i;
		Snake[0].now = -1;
	}
	for(i = 0; i < H; i++)
	{
		for(j = 0; j < W; j++)
			printf("%c",GameMap[i][j]);
		printf("\n");
	}
}

void Check_Border()  //检查蛇头是否越界  
{  
 	if(Snake[0].x < 0 || Snake[0].x >= H || Snake[0].y < 0 || Snake[0].y >= W)  
     	over = 1;  
}  

void Check_Head(int x, int y)  //检查蛇头移动后的位置情况  
{      
 	if(GameMap[ Snake[0].x ][ Snake[0].y ] == ' ')  //为空  
  		GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';   
  	else if(GameMap[ Snake[0].x ][ Snake[0].y ] == '$')  //为食物  
  		{  
   			GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';    
   			Snake[sum].x = x;   //新增加的蛇身为蛇头后面的那个  
     		Snake[sum].y = y;  
    		Snake[sum].now = Snake[0].now;  
      	   	GameMap[ Snake[sum].x ][ Snake[sum].y ] = 'X';   
   			sum++;   
  		}  
  	else 
   		over = 1;  
}

void Move()   //蛇的移动  
{  
 	int x, y;  
    int t = sum;  //保存当前蛇的长度  
 	//记录当前蛇头的位置,并设置为空,蛇头先移动  
 	x = Snake[0].x;  y = Snake[0].y;  GameMap[x][y] = ' ';  
 	Snake[0].x = Snake[0].x + dx[ Snake[0].now ];  
 	Snake[0].y = Snake[0].y + dy[ Snake[0].now ];  
 	Check_Border();   //蛇头是否越界  
 	Check_Head(x, y);  //蛇头移动后的位置情况,参数为: 蛇头的开始位置  
	if(sum == t)  //未吃到食物即蛇身移动哦  
		for(i = 1; i < sum; i++)  //要从蛇尾节点向前移动哦,前一个节点作为参照  
	 	{  
	  		if(i == 1)   //尾节点设置为空再移动  
	   			GameMap[ Snake[i].x ][ Snake[i].y ] = ' ';   
	  		if(i == sum-1)  //为蛇头后面的蛇身节点,特殊处理  
	  		{  
	   			Snake[i].x = x;  
	         	Snake[i].y = y;  
	    		Snake[i].now = Snake[0].now;  
	  		}  
	  		else   //其他蛇身即走到前一个蛇身位置  
	  		{  
	   			Snake[i].x = Snake[i+1].x;  
	         	Snake[i].y = Snake[i+1].y;  
	      		Snake[i].now = Snake[i+1].now;  
	  		}	     
	  		GameMap[ Snake[i].x ][ Snake[i].y ] = 'X'; //移动后要置为'X'蛇身   
	 	} 
}  

```

#### snake.eat.c

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#define H 10//地图的高 
#define W 10//地图的宽
#define w 119
#define a 97
#define s 115
#define d 100
int i, j;//循环变量 
int sum = 5;//蛇的长度
int over = 0;//游戏结束标志（自吃或者碰墙）
int dx[4] = {0, 0, -1, 1}; //左右移动
int dy[4] = {-1, 1, 0, 0}; //上下移动

struct Snake{//蛇的每个结点的数据类型 
	int x, y;
	int now;//保存当前结点的方向，0、1、2、3分别为左右上下 
}Snake[H*W];

const char Shead = 'H';
const char Sbody = 'X';
const char Sfood = '$';
const char Snode = ' ';
const char Swall = '*';

void Initial();//地图的初始化
void Create_Food();//产生食物
void Show(); //刷新显示地图 
void Move(); //蛇的移动
void Check_Border();//检查蛇头是否越界
void Check_Head(int x, int y); //检查蛇头移动后的情况

char GameMap[H][W];//游戏地图 

int main()
{
	srand(time(NULL)); 
	Initial();
	while(1)
	{
		int ch;
		ch = getchar();
		switch(ch){
			case a: Snake[0].now = 0,Move(); 
					break;				
			case d: Snake[0].now = 1,Move();
					break;
			case w:	Snake[0].now = 2,Move();
					break;
			case s:	Snake[0].now = 3,Move();
					break;
		}	
		if(over)  //自吃或碰墙即游戏结束  
  		{   
   			printf("\n**游戏结束**\n"); 
			printf("你的得分为：%d",sum); 
     		break;  
  		} 
  		if(sum == ((H-2)*(W-2)-1))
  		{
  			printf("/nYou win!/n");//吃到没得吃了 
  			break;
		}
  		system("cls");   //清空地图再显示刷新好的地图 
  		for(i = 0; i < H; i++)   
  		{   
   			for(j = 0; j < W; j++)  
    		printf("%c", GameMap[i][j]);  
   			printf("\n");  
  		}  
	}
	return 0;
 } 

void Initial()
{
	memset(GameMap, ' ', sizeof(GameMap));
	for(i=0; i<W; i++)
	{
		GameMap[0][i] = '*';
		GameMap[H-1][i] = '*';
	}
	for(i=0; i<H; i++)
	{
		GameMap[i][0] = '*';
		GameMap[i][W-1] = '*';
	}
	for(i=1; i<5; i++)
		GameMap[1][i] = 'X';
	GameMap[1][5] = 'H';
	Snake[0].x = 1; Snake[0].y = 5;
	Snake[0].now = -1;
	for(i=1; i<5; i++)
	{
		Snake[i].x = 1;
		Snake[i].y = i;
		Snake[0].now = -1;
	}
	Create_Food();   //随机产生食物  
	for(i = 0; i < H; i++)
	{
		for(j = 0; j < W; j++)
			printf("%c",GameMap[i][j]);
		printf("\n");
	}
}

void Check_Border()  //检查蛇头是否越界  
{  
 	if(Snake[0].x < 0 || Snake[0].x >= H || Snake[0].y < 0 || Snake[0].y >= W)  
     	over = 1;  
}  

void Check_Head(int x, int y)  //检查蛇头移动后的位置情况  
{      
 	if(GameMap[ Snake[0].x ][ Snake[0].y ] == ' ')  //为空  
  		GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';   
  	else if(GameMap[ Snake[0].x ][ Snake[0].y ] == '$')  //为食物  
  		{  
   			GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';    
   			Snake[sum].x = x;   //新增加的蛇身为蛇头后面的那个  
     		Snake[sum].y = y;  
    		Snake[sum].now = Snake[0].now;  
      	   	GameMap[ Snake[sum].x ][ Snake[sum].y ] = 'X';   
   			sum++;  
   			Create_Food();  //食物吃完了马上再产生一个食物  
  		}  
  	else 
   		over = 1;  
}

void Move()   //蛇的移动  
{  
 	int x, y;  
    int t = sum;  //保存当前蛇的长度  
 	//记录当前蛇头的位置,并设置为空,蛇头先移动  
 	x = Snake[0].x;  y = Snake[0].y;  GameMap[x][y] = ' ';  
 	Snake[0].x = Snake[0].x + dx[ Snake[0].now ];  
 	Snake[0].y = Snake[0].y + dy[ Snake[0].now ];  
 	Check_Border();   //蛇头是否越界  
 	Check_Head(x, y);  //蛇头移动后的位置情况,参数为: 蛇头的开始位置  
	if(sum == t)  //未吃到食物即蛇身移动哦  
		for(i = 1; i < sum; i++)  //要从蛇尾节点向前移动哦,前一个节点作为参照  
	 	{  
	  		if(i == 1)   //尾节点设置为空再移动  
	   			GameMap[ Snake[i].x ][ Snake[i].y ] = ' ';   
	  		if(i == sum-1)  //为蛇头后面的蛇身节点,特殊处理  
	  		{  
	   			Snake[i].x = x;  
	         	Snake[i].y = y;  
	    		Snake[i].now = Snake[0].now;  
	  		}  
	  		else   //其他蛇身即走到前一个蛇身位置  
	  		{  
	   			Snake[i].x = Snake[i+1].x;  
	         	Snake[i].y = Snake[i+1].y;  
	      		Snake[i].now = Snake[i+1].now;  
	  		}	     
	  		GameMap[ Snake[i].x ][ Snake[i].y ] = 'X'; //移动后要置为'X'蛇身   
	 	} 
}  

void Create_Food()  //在地图上随机产生食物  
{  
 	int fx, fy;  
 	while(1)  
 	{  
  		fx = rand()%H;  
     	fy = rand()%W;     
  		if(GameMap[fx][fy] == ' ')  //不能出现在蛇所占有的位置  
  		{   
   			GameMap[fx][fy] = Sfood;  
      		break;  
  		}  
 	}  
} 
```











