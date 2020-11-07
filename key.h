#pragma once

#include <graphics.h>
#include "Node.h"
#include <deque>
#include <thread>
#include "mydelay.h"
#include "sound.h"

/////////////////////////////////////////////
// ���峣����ö�������ṹ�塢ȫ�ֱ���
/////////////////////////////////////////////

#define	CMD_UP				1	//W
#define	CMD_DOWN		2		//S
#define	CMD_LEFT			4		//A
#define	CMD_RIGHT			8		//D
#define	CMD_SHOOT		16


/////////////////////////////////////////////
// ��������
/////////////////////////////////////////////

int  GetCommand();					// ��ȡ��������
void DispatchCommand(int _cmd, deque<Node>& shot, int& x, int& y, int step,int &shoot_time);		// �ַ���������
void OnUp(int &x,int &y, int step);						// ����
void OnDown(int& x, int& y, int step);						// ����
void OnLeft(int& x, int& y, int step);						// ����
void OnRight(int& x, int& y, int step);						// ����
void OnShoot(deque<Node>& shot, int x, int y,int );




// ��ȡ��������
int GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState('A') & 0x8000)		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)	c |= CMD_RIGHT;
	if (GetAsyncKeyState('W') & 0x8000)		c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)		c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)		c |= CMD_SHOOT;
	
	return c;
}

// �ַ���������
void DispatchCommand(int _cmd, deque<Node>& shot,int &x,int&y,int step, int &shoot_time)
{
	if (_cmd & CMD_UP)			OnUp(x,y,step);
	if (_cmd & CMD_DOWN)		OnDown(x, y, step);
	if (_cmd & CMD_LEFT)		OnLeft(x, y, step);
	if (_cmd & CMD_RIGHT)		OnRight(x, y, step);
	if (_cmd & CMD_SHOOT)		OnShoot(shot,x, y,shoot_time);
}

// ����
void OnUp(int &x,int &y,int step)
{
	if (y > 60)
		y -= step;
}


// ����
void OnDown(int& x, int& y, int step)
{
	if (y < 600 - 60)
		y += step;
}

// ����
void OnLeft(int& x, int& y, int step)
{
	if (x >= 50)
		x -= step;
}

// ����
void OnRight(int& x, int& y, int step)
{
	if (x < 1000 - 50)
		x += step;
}


void OnShoot(deque<Node>& shot, int x, int y,int n)
{
	int shot_type = n;	//1: һ���ӵ� 2: �����ӵ�

	if (shot_type == 1)
	{
		Node t;
		t.x = x;
		t.y = y - 60;
		shot.push_back(t);
	}
	if (shot_type == 2)
	{
		Node t1,t2;
		t1.x = x - 10;
		t1.y = y - 60;
		t2.x = x + 10;
		t2.y = y - 60;
		shot.push_back(t1);
		shot.push_back(t2);
			
	}
	if (shot_type == 3)
	{
		Node t1, t2,t3;
		t1.x = x - 20;
		t1.y = y - 60;
		t2.x = x;
		t2.y = y - 60;
		t3.x = x + 20;
		t3.y = y - 60;
		shot.push_back(t1);
		shot.push_back(t2);
		shot.push_back(t3);

	}
	if (shot_type == 5)
	{
		for (int i = 600-60; i > 0; i -= 10)
		{
			Node t1, t2, t3;
			t1.x = x - 20;
			t1.y = i;
			t2.x = x;
			t2.y =i;
			t3.x = x + 20;
			t3.y = i;
			shot.push_back(t1);
			shot.push_back(t2);
			shot.push_back(t3);
			
		}
		

	}
	playShot();
	
}