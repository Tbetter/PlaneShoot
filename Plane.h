#pragma once
#include <iostream>
using namespace std;
#include <easyx.h>
#include <conio.h>
#include <string>
#include <graphics.h>
#include <queue>
#include <algorithm>
#include <ctime>
#include <sys/timeb.h>
#include <thread>
#include "Node.h"
#include "mydelay.h"
#include "sound.h"

class Plane
{
public:
	Plane()
	{
		x = 500;
		y = 400;
		life = 5;
		score = 0;
	}
	void showPlane(int x, int y)
	{
		loadimage(&plane1, _T("plane1.png"), 50, 60);
		putimage(x, y, &plane1, SRCPAINT);
		this->x = x;
		this->y = y;
	}
	void shoot(deque<Node> &s)
	{
		int len = (int)s.size();
		int i;
		IMAGE imgShot;
		loadimage(&imgShot, _T("shot.png"), 50, 60);
		for (i = 0; i < len; i++)
		{
			Node t = s.front();
			s.pop_front();
			t.y -= 25;
			if (t.y <= 0)continue;
			putimage(t.x, t.y , &imgShot, SRCPAINT);
			s.push_back(t);		
		}
		
	}

	void attacked()
	{
		life--;
	}
	IMAGE plane1;
	
	int x;
	int y;
	int life;
	int score;
};


class Foe
{
public:
	void showFoe(deque<Node>& f)
	{
		int len = (int)f.size();
		int i;
		IMAGE foe;
		setSrand();
		loadimage(&foe, _T("foe.png"), 50, 60);
		for (i = 0; i < len; i++)
		{
			Node t = f.front();
			f.pop_front();
			
			moveCule(t);

			if (t.y >= 600)continue;
			putimage(t.x, t.y, &foe, SRCPAINT);
			f.push_back(t);
		}
	}
	void shoot(deque<Node>& s)
	{
		int len = (int)s.size();
		int i;
		IMAGE imgShot;
		loadimage(&imgShot, _T("shot.png"), 50, 60);
		for (i = 0; i < len; i++)
		{
			Node t = s.front();
			s.pop_front();
			t.y -= 25;
			if (t.y <= 0)continue;
			putimage(t.x, t.y, &imgShot, SRCPAINT);
			s.push_back(t);
		}

	}

	void moveCule(Node &t)
	{
		if (t.dir == 1)
		{	
				t.x += 15;
				if (t.x >= 1000 - 60)
				{
					t.dir = 2;
				}
		}

		if (t.dir == 2)
		{
			t.x -= 15;
			if (t.x <= 60)
			{
				t.dir = 1;
			}
		}
		
		t.y += 10;
	}

	void setSrand()
	{
		struct timeb timeSeed;
		ftime(&timeSeed);
		srand((unsigned int)(timeSeed.time * 1000 + timeSeed.millitm));  // milli time
	}
};


class Boom
{
public:
	Boom()
	{
	}
	void showBoom(int x, int y)
	{
		loadimage(&IMGboom, _T("boom.png"), 50, 60);
		putimage(x, y, &IMGboom, SRCPAINT);
	}
	

	void check(deque<Node>& s, deque<Node>& f,Plane &p)
	{
		deque<Node>::iterator ts;
		int flag=0;
		for (deque<Node>::iterator its = s.begin(); its != s.end(); its++)
		{
			deque<Node>::iterator tf = find(f.begin(), f.end(), *its);
			
			if (tf != f.end())
			{
				ts = its;
				flag = 1;
				int x = tf->x;
				int y = tf->y;
				f.erase(tf);
				showBoom(x, y);
				playBoom();
				p.score += 10;
			}
		}
		if (flag)
		{
			s.erase(ts);
		}
	}

	void checkPlane(deque<Node>& f,Plane& p)
	{
		deque<Node>::iterator tf;
		int flag = 0;
		for (deque<Node>::iterator it = f.begin(); it != f.end(); it++)
		{
			if ((p.x > it->x - 25 && p.x <= it->x + 25) && (p.y > it->y - 30 && p.y <= it->y + 30))
			{
				tf = it;
				flag = 1;
				break;
			}
		}
		if (flag)
		{
			f.erase(tf);
			p.attacked();
			if (p.life == 0)
			{
				showBoom(p.x, p.y);
				playBoom();
			}
		}
	}

	IMAGE IMGboom;
	
};


