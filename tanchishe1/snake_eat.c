#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#define H 10//��ͼ�ĸ� 
#define W 10//��ͼ�Ŀ�
#define w 119
#define a 97
#define s 115
#define d 100
int i, j;//ѭ������ 
int sum = 5;//�ߵĳ���
int over = 0;//��Ϸ������־���ԳԻ�����ǽ��
int dx[4] = {0, 0, -1, 1}; //�����ƶ�
int dy[4] = {-1, 1, 0, 0}; //�����ƶ�

struct Snake{//�ߵ�ÿ�������������� 
	int x, y;
	int now;//���浱ǰ���ķ���0��1��2��3�ֱ�Ϊ�������� 
}Snake[H*W];

const char Shead = 'H';
const char Sbody = 'X';
const char Sfood = '$';
const char Snode = ' ';
const char Swall = '*';

void Initial();//��ͼ�ĳ�ʼ��
void Create_Food();//����ʳ��
void Show(); //ˢ����ʾ��ͼ 
void Move(); //�ߵ��ƶ�
void Check_Border();//�����ͷ�Ƿ�Խ��
void Check_Head(int x, int y); //�����ͷ�ƶ�������

char GameMap[H][W];//��Ϸ��ͼ 

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
		if(over)  //�ԳԻ���ǽ����Ϸ����  
  		{   
   			printf("\n**��Ϸ����**\n"); 
			printf("��ĵ÷�Ϊ��%d",sum); 
     		break;  
  		} 
  		if(sum == ((H-2)*(W-2)-1))
  		{
  			printf("/nYou win!/n");//�Ե�û�ó��� 
  			break;
		}
  		system("cls");   //��յ�ͼ����ʾˢ�ºõĵ�ͼ 
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
	Create_Food();   //�������ʳ��  
	for(i = 0; i < H; i++)
	{
		for(j = 0; j < W; j++)
			printf("%c",GameMap[i][j]);
		printf("\n");
	}
}

void Check_Border()  //�����ͷ�Ƿ�Խ��  
{  
 	if(Snake[0].x < 0 || Snake[0].x >= H || Snake[0].y < 0 || Snake[0].y >= W)  
     	over = 1;  
}  

void Check_Head(int x, int y)  //�����ͷ�ƶ����λ�����  
{      
 	if(GameMap[ Snake[0].x ][ Snake[0].y ] == ' ')  //Ϊ��  
  		GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';   
  	else if(GameMap[ Snake[0].x ][ Snake[0].y ] == '$')  //Ϊʳ��  
  		{  
   			GameMap[ Snake[0].x ][ Snake[0].y ] = 'H';    
   			Snake[sum].x = x;   //�����ӵ�����Ϊ��ͷ������Ǹ�  
     		Snake[sum].y = y;  
    		Snake[sum].now = Snake[0].now;  
      	   	GameMap[ Snake[sum].x ][ Snake[sum].y ] = 'X';   
   			sum++;  
   			Create_Food();  //ʳ������������ٲ���һ��ʳ��  
  		}  
  	else 
   		over = 1;  
}

void Move()   //�ߵ��ƶ�  
{  
 	int x, y;  
    int t = sum;  //���浱ǰ�ߵĳ���  
 	//��¼��ǰ��ͷ��λ��,������Ϊ��,��ͷ���ƶ�  
 	x = Snake[0].x;  y = Snake[0].y;  GameMap[x][y] = ' ';  
 	Snake[0].x = Snake[0].x + dx[ Snake[0].now ];  
 	Snake[0].y = Snake[0].y + dy[ Snake[0].now ];  
 	Check_Border();   //��ͷ�Ƿ�Խ��  
 	Check_Head(x, y);  //��ͷ�ƶ����λ�����,����Ϊ: ��ͷ�Ŀ�ʼλ��  
	if(sum == t)  //δ�Ե�ʳ�Ｔ�����ƶ�Ŷ  
		for(i = 1; i < sum; i++)  //Ҫ����β�ڵ���ǰ�ƶ�Ŷ,ǰһ���ڵ���Ϊ����  
	 	{  
	  		if(i == 1)   //β�ڵ�����Ϊ�����ƶ�  
	   			GameMap[ Snake[i].x ][ Snake[i].y ] = ' ';   
	  		if(i == sum-1)  //Ϊ��ͷ���������ڵ�,���⴦��  
	  		{  
	   			Snake[i].x = x;  
	         	Snake[i].y = y;  
	    		Snake[i].now = Snake[0].now;  
	  		}  
	  		else   //���������ߵ�ǰһ������λ��  
	  		{  
	   			Snake[i].x = Snake[i+1].x;  
	         	Snake[i].y = Snake[i+1].y;  
	      		Snake[i].now = Snake[i+1].now;  
	  		}	     
	  		GameMap[ Snake[i].x ][ Snake[i].y ] = 'X'; //�ƶ���Ҫ��Ϊ'X'����   
	 	} 
}  

void Create_Food()  //�ڵ�ͼ���������ʳ��  
{  
 	int fx, fy;  
 	while(1)  
 	{  
  		fx = rand()%H;  
     	fy = rand()%W;     
  		if(GameMap[fx][fy] == ' ')  //���ܳ���������ռ�е�λ��  
  		{   
   			GameMap[fx][fy] = Sfood;  
      		break;  
  		}  
 	}  
} 
