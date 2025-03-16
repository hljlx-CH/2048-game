/*	��һ���������ӡ+�ƶ��ϲ�������д
	�ڶ����������������+��ȡ��λ���������к�����д
	�������������Ƿ�����+���������Ƿ��ܼ����ϲ�+��Ϸ����+��Ϸ�ɹ��ĺ�����д
	���Ĳ�����ʼ����Ϸ����+��ͼƬ�����ֶ�Ӧ����
	���岽��ʵ�ְ�������

	���㣺��ȡ��λ���е�˼·���ж����������Ƿ�ɼ����ϲ���˼·

	���ѧϰ�ĵ㣺ָ�롢�ṹ��
*/

//�����д�����������ڵ������ַ�����������ת�������ͣ�������Ҫ��������_T("����")
#undef UNICODE
#undef _UNICODE			

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <conio.h>

//���ھ��
HWND window;

//��������
int array[4][4] = {0};

int nullcount;				//��¼��λ����
int nullpos[2][16] = {0};	//��¼��λ������λ�õ�����

//��ӡ���麯��
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

//��ȡ��λ������
int getnullpos()
{
	nullcount = 0;
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if (array[row][column] == 0)
			{
				nullpos[0][nullcount] = row;		//�����λ��
				nullpos[1][nullcount] = column;		//�����λ��
				nullcount++;
			}
	return nullcount;

}

//�����������
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
			if (array[row][column] != 0)	i--;		//���⵱���ɶ���������ʱ����ͬһλ�ö������
			array[row][column] = (rand() % 2 + 1) * 2;
		}
	}

}
	
//����+�ϲ�����
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

//����+�ϲ�����
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

//����+�ϲ�����
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

//����+�ϲ�����
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

//���16�������Ƿ��Լ����ˡ����пշ���1��û�пշ���0��
int isfull()
{
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if (array[row][column] == 0)
				return 1;
	return 0;
}

//����Ƿ񻹺��п��Ժϲ�������,�пɺϲ��ķ���1��û�п��Ժϲ�����ʱ����0
int ismerge()
{
	for (int row = 0; row < 4; row++)
		for (int column = 0; column < 4; column++)
			if ((row + 1 < 4) && (array[row][column] == array[row + 1][column]) ||
				(array[row][column] == array[row][column + 1])&&(column + 1 <4))		//�ǵ����ȼ�>��
				return 1;
	return 0;
}

int gameover()
{
	if ((isfull() == 0) && (ismerge() == 0))
	{
		settextcolor(WHITE);
		settextstyle(100, 0, _T("����"));
		outtextxy(20, 200, _T("��Ϸ����"));
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
				settextstyle(100, 0, _T("����"));
				outtextxy(20, 200, _T("�ɹ��ϳ�"));
				return 1;
			}

		}
	return 0;



}

//��easyx�����ʼ����Ϸ����
void initwindow()
{
	initgraph(450, 550, EX_SHOWCONSOLE);
//	window = initgraph(450, 550, EX_SHOWCONSOLE);
	window = GetHWnd();

	SetWindowText(window, "2048С��Ϸ");

	settextcolor(RED);
	settextstyle(60,0,"����");		
	outtextxy(60,0, "2048С��Ϸ");	
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

//��ȡ����״̬
//��������
void getkeyboard1()
{
	while (IsWindow(window))
	{
		gamesussce();
		gameover();
		if ((gamesussce() == 0) && (gameover() == 0))
		{
			ExMessage msg;

			if (false == peekmessage(&msg))//peekmessage���������Ƿ�����Ϣ���᷵�أ��˺������ڴ�������ʱ��Ч
				continue;
			if (msg.message == WM_KEYUP)//����̧��ʱ���
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

//����̨����
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
				char key = _getch();//		��-72����-80����-75����-77���˺���ֻ���ڿ���̨����ʱ������

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

	getkeyboard1();//2048�ô˺���
}