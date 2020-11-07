#pragma once

#include <graphics.h>
#include "Node.h"
#include <deque>
#include <thread>
#include "mydelay.h"
#include "sound.h"

/////////////////////////////////////////////
// 定义常量、枚举量、结构体、全局变量
/////////////////////////////////////////////

#define	CMD_UP				1	//W
#define	CMD_DOWN		2		//S
#define	CMD_LEFT			4		//A
#define	CMD_RIGHT			8		//D
#define	CMD_SHOOT		16


/////////////////////////////////////////////
// 函数声明
/////////////////////////////////////////////

int  GetCommand();					// 获取控制命令
void DispatchCommand(int _cmd, deque<Node>& shot, int& x, int& y, int step,int &shoot_time);		// 分发控制命令
void OnUp(int &x,int &y, int step);						// 上移
void OnDown(int& x, int& y, int step);						// 下移
void OnLeft(int& x, int& y, int step);						// 左移
void OnRight(int& x, int& y, int step);						// 右移
void OnShoot(deque<Node>& shot, int x, int y,int );




// 获取控制命令
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

// 分发控制命令
void DispatchCommand(int _cmd, deque<Node>& shot,int &x,int&y,int step, int &shoot_time)
{
	if (_cmd & CMD_UP)			OnUp(x,y,step);
	if (_cmd & CMD_DOWN)		OnDown(x, y, step);
	if (_cmd & CMD_LEFT)		OnLeft(x, y, step);
	if (_cmd & CMD_RIGHT)		OnRight(x, y, step);
	if (_cmd & CMD_SHOOT)		OnShoot(shot,x, y,shoot_time);
}

// 上移
void OnUp(int &x,int &y,int step)
{
	if (y > 60)
		y -= step;
}


// 下移
void OnDown(int& x, int& y, int step)
{
	if (y < 600 - 60)
		y += step;
}

// 左移
void OnLeft(int& x, int& y, int step)
{
	if (x >= 50)
		x -= step;
}

// 右移
void OnRight(int& x, int& y, int step)
{
	if (x < 1000 - 50)
		x += step;
}


void OnShoot(deque<Node>& shot, int x, int y,int n)
{
	int shot_type = n;	//1: 一发子弹 2: 两发子弹

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