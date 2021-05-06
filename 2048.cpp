#pragma warning(disable:4996)
#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<graphics.h>
#define GRID_W 100    //格子的宽度
#define MAX_SIZE 4    //格子数量
#define INTERVAL 15   //格子的间距
#define WIN_SIZE MAX_SIZE*GRID_W+INTERVAL*(1+MAX_SIZE)
enum Color
{
	t0 = RGB(205, 193, 180),
	t1 = RGB(238, 228, 218),
	t2 = RGB(237, 224, 200),
	t3 = RGB(242, 177, 121),
	t4 = RGB(245, 149, 99),
	t5 = RGB(246, 124, 95),
	t6 = RGB(246, 94, 59),
	t7 = RGB(242, 177, 121),
	t8 = RGB(237, 204, 97),
	t9 = RGB(255, 0, 128),
	t10 = RGB(145, 0, 72),
	t11 = RGB(242, 17, 158),
	back = RGB(187, 173, 160),
};
Color arr[13] = { t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,back };
//定义数据
int map[MAX_SIZE][MAX_SIZE];
//随机产生两个整数
int createNum(int i)
{
	srand((unsigned)time(NULL) + i);
	if (rand() % 5 == 0)
		return 4;
	else return 2;
}
//初始化数据
void gameInit()
{
	for (int i = 0; i < 2;)
	{
		int r = rand() % MAX_SIZE;
		int c = rand() % MAX_SIZE;
		if (map[r][c] == 0)
		{
			map[r][c] = createNum(i);
			i++;
		}
	}
}
//绘制界面
void gameDraw()
{
	setbkcolor(RGB(187, 173, 160));
	cleardevice();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int k = 0; k < MAX_SIZE; k++)
		{
			int x, y; 
			x = GRID_W * k + (k + 1) * INTERVAL;
			y = GRID_W * i + (i + 1) * INTERVAL;
			int index = (int)log2((double)map[i][k]);
 			COLORREF tcolor = arr[index];
			setfillcolor(tcolor);
			solidroundrect(x, y, x + GRID_W, y + GRID_W, 10, 10);
			if (map[i][k])
			{
				char str[10] = "";
				sprintf(str, "%d", map[i][k]);
				settextstyle(50, 0, "黑体");
				setbkmode(TRANSPARENT);
				settextcolor(RGB(119, 110, 101));
				int tw = textwidth(str);
				int th = textheight(str);
				int tx = (GRID_W - tw) / 2;
				int ty = (GRID_W - th) / 2;
				outtextxy(x + tx, y + ty, (str));
			}
		}
		printf("\n");
	}
}
//开始游戏
void moveUp()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_SIZE; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] *= 2;
					map[begin][i] = 0;
					temp++;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)
						map[begin][i] = 0;
					temp++;
				}
			}
		}
	}
}
void moveDowm()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = MAX_SIZE-1;
		for (int begin = MAX_SIZE-2; begin >= 0; begin--)
		{
			if (map[begin][i] != 0)
			{ 
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] *= 2;
					map[begin][i] = 0;
					temp--;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
						map[begin][i] = 0;
					temp--;
				}
			}
		}
	}
}
void moveLeft()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_SIZE; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] *= 2;
					map[i][begin] = 0;
					temp++;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
						map[i][begin] = 0;
					temp++;
				}
			}
		}
	}
}
void moveRight()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = MAX_SIZE - 1;
		for (int begin = MAX_SIZE - 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] *= 2;
					map[i][begin] = 0;
					temp--;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
						map[i][begin] = 0;
					temp--;
				}
			}
		}
	}
}
void keyDeal()
{
	char key = _getch();
	int flag = 0;
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		moveUp();
		flag = 1;
		break;
	case 's':
	case 'S':
	case 80:
		moveDowm();
		flag = 1;
		break;
	case 'a':
	case 'A':
	case 75:
		moveLeft();
		flag = 1;
		break;
	case 'd':
	case 'D':
	case 77:
		moveRight();
		flag = 1;
		break;
	}
	if (flag == 1)
	{
		while (1)
		{
			int r = rand() % MAX_SIZE;
			int c = rand() % MAX_SIZE;
			if (map[r][c] == 0)
			{
				map[r][c] = createNum((int)key);
				break;
			}
		}
	}
}
int main()
{
	initgraph(WIN_SIZE, WIN_SIZE);
	gameInit();
	while (1)
	{
		gameDraw();
		keyDeal();
	};
	closegraph();
	return 0;
}
