/*	第一步：数组打印+移动合并函数编写
	第二步：随机数的生成+获取空位数量与行列函数编写
	第三步：格子是否已满+相邻数字是否还能继续合并+游戏结束+游戏成功的函数编写
	第四步：初始化游戏界面+将图片与数字对应起来
	第五步：实现按键操作

	亮点：获取空位行列的思路、判断相邻数字是否可继续合并的思路

	需加学习的点：指针、结构体
*/

//此两行代码的作用在于当输入字符串是无需在转换其类型，负责需要这样输入_T("黑体")
#undef UNICODE
#undef _UNICODE			

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <conio.h>

//窗口句柄
HWND window;

//定义数组
int array[4][4] = {0};

int nullcount;				//记录空位数量
int nullpos[2][16] = {0};	//记录空位的行列位置的数组

//打印数组函数
void printfarray()
{
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			printf("%d\t", array[row][column]);
		}
		printf("\n");
	}
}

//获取空位的行列
int getnullpos()
{
	nullcount = 0;
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if (array[row][column] == 0)
			{
				nullpos[0][nullcount] = row;		//贮存空位行
				nullpos[1][nullcount] = column;		//贮存空位列
				nullcount++;
			}
	return nullcount;

}

//随机数的生成
void creatranddate(int count)
{
	if (getnullpos() != 0)
	{
		srand(time(0));
		for (int i = 0; i < count; i++)
		{
			int pos = rand() % nullcount;
			int row = nullpos[0][pos];
			int column = nullpos[1][pos];
			if (array[row][column] != 0)	i--;		//避免当生成多个随机数的时候在同一位置多次生成
			array[row][column] = (rand() % 2 + 1) * 2;
		}
	}

}
	
//左移+合并函数
void left()
{
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			if (array[row][column] == 0)
			{
				for (int t = column + 1; t < 4;t++)
					if (array[row][t] != 0)
					{
						array[row][column] = array[row][t];
						array[row][t] = 0;
						break;
					}
			}
			
			if (array[row][column] != 0)
				for (int t = column + 1; t < 4; t++)
				{
					if (array[row][t] == array[row][column])
					{
						array[row][column] *= 2;
						array[row][t] = 0;
						break;
					}
					else if (array[row][t] == 0)
						continue;
					else break;
				}

		}
	}
	creatranddate(1);
}

//右移+合并函数
void right()
{
	for (int row = 0; row < 4; row++)
	{
		for (int column = 3; column >= 0; column--)
		{
			if (array[row][column] == 0)
			{
				for (int t = column - 1; t >=0 ; t--)
					if (array[row][t] != 0)
					{
						array[row][column] = array[row][t];
						array[row][t] = 0;
						break;
					}
			}
			if (array[row][column] != 0)
			{
				for (int t = column - 1; t >= 0; t--)
					if (array[row][t] == array[row][column])
					{
						array[row][column] *= 2;
						array[row][t] = 0;
						break;
					}
					else if (array[row][t] == 0)
						continue;
					else break;

			}
		}
	}
	creatranddate(1);
}

//上移+合并函数
void up()
{
	for (int column = 0; column < 4; column++)
	{
		for (int row = 0; row < 4; row++)
		{
			if (array[row][column] == 0)
			{
				for (int t = row + 1; t < 4; t++)
					if (array[t][column] != 0)
					{
						array[row][column] = array[t][column];
						array[t][column] = 0;
						break;
					}
			}
			if (array[row][column] != 0)
			{
				for (int t = row + 1; t < 4; t++)
					if (array[t][column] == array[row][column])
					{
						array[row][column] *= 2;
						array[t][column] = 0;
						break;
					}
					else if (array[t][column] == 0)
						continue;
					else break;

			}
		}
	}
	creatranddate(1);
}

//下移+合并函数
void down()
{
	for (int column = 0; column < 4; column++)
	{
		for (int row = 3; row >=0; row--)
		{
			if (array[row][column] == 0)
			{
				for (int t = row - 1; t >=0; t--)
					if (array[t][column] != 0)
					{
						array[row][column] = array[t][column];
						array[t][column] = 0;
						break;
					}
			}
			if (array[row][column] != 0)
			{
				for (int t = row - 1; t >= 0; t--)
					if (array[t][column] == array[row][column])
					{
						array[row][column] *= 2;
						array[t][column] = 0;
						break;
					}
					else if (array[t][column] == 0)
						continue;
					else break;
			}
		}
	}
	creatranddate(1);
}

//检测16个格子是否以及满了——有空返回1，没有空返回0；
int isfull()
{
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if (array[row][column] == 0)
				return 1;
	return 0;
}

//检测是否还含有可以合并的数字,有可合并的返回1，没有可以合并的数时返回0
int ismerge()
{
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if ((row + 1 < 4) && (array[row][column] == array[row + 1][column]) ||
				(array[row][column] == array[row][column + 1])&&(column + 1 <4))		//非的优先级>或
				return 1;
	return 0;
}

int gameover()
{
	if ((isfull() == 0) && (ismerge() == 0))
	{
		settextcolor(WHITE);
		settextstyle(100, 0, _T("黑体"));
		outtextxy(20, 200, _T("游戏结束"));
		return 1;
	}

	return 0;
}

int gamesussce()
{

	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
		{
			if (array[row][column] == 2048)
			{

				settextcolor(WHITE);
				settextstyle(100, 0, _T("黑体"));
				outtextxy(20, 200, _T("成功合成"));
				return 1;
			}

		}
	return 0;



}

//用easyx插件初始化游戏界面
void initwindow()
{
	initgraph(450, 550, EX_SHOWCONSOLE);
//	window = initgraph(450, 550, EX_SHOWCONSOLE);
	window = GetHWnd();

	SetWindowText(window, "2048小游戏");

	settextcolor(RED);
	settextstyle(60,0,"仿宋");		
	outtextxy(60,0, "2048小游戏");	
}

void number_link_picture()
{
	IMAGE img;

	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
		{
			int a = array[row][column];
			switch (a)
			{
			case 0:	loadimage(&img, _T("image1/0.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 2:	loadimage(&img, _T("image1/2.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 4:	loadimage(&img, _T("image1/4.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 8:	loadimage(&img, _T("image1/8.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 16:loadimage(&img, _T("image1/16.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 32:loadimage(&img, _T("image1/32.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 64:loadimage(&img, _T("image1/64.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 128:	loadimage(&img, _T("image1/128.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 256:	loadimage(&img, _T("image1/256.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 512:	loadimage(&img, _T("image1/512.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 1024:loadimage(&img, _T("image1/1024.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			case 2048:	loadimage(&img, _T("image1/2048.bmp"));
				putimage(10 + column * 110, 70 + row * 110, &img);
				break;
			default: break;
			}
		}
}

//获取按键状态
//窗口输入
void getkeyboard1()
{
	while (IsWindow(window))
	{
		gamesussce();
		gameover();
		if ((gamesussce() == 0) && (gameover() == 0))
		{
			ExMessage msg;

			if (false == peekmessage(&msg))//peekmessage函数无论是否有消息都会返回，此函数是在窗口输入时有效
				continue;
			if (msg.message == WM_KEYUP)//按键抬起时检测
			{
				switch (msg.vkcode)
				{
				case VK_UP:	up();
					break;
				case VK_DOWN:down();
					break;
				case VK_LEFT:left();
					break;
				case VK_RIGHT:right();
					break;
				default:continue;

				}
				number_link_picture();
			}
		}
	}
}

//控制台输入
void getkeyboard5()
{
	while (IsWindow(window))
	{
		gamesussce();
		gameover();
		if ((gamesussce() == 0) && (gameover() == 0))
		{
			if (_kbhit())
			{
				char key = _getch();//		上-72，下-80，左-75，右-77，此函数只有在控制台输入时才有用

				switch (key)
				{
				case 72:up();
					printf("shang");
					break;
				case 80:down();
					break;
				case 75:left();
					break;
				case 77:right();
					break;
				default:continue;
				}
				number_link_picture();
			}
		}
	}
}

void main()
{

	creatranddate(1);
	initwindow();
	number_link_picture();

	getkeyboard1();//2048用此函数
}