#include "Plane.h"
#include "key.h"
#include <deque>
#include <ctime>
#include "font.h"

IMAGE bg;
deque<Node> shot;
deque<Node> f;

void bgShow()
{
	loadimage(&bg, _T("bg.jpg"), 1000, 600);
	putimage(0, 0, &bg);
}

//���˳���
void foeFun()
{
	Node t;
	t.x = (rand())%1000;
	t.y = 60;
	t.dir = rand()%2+1;
	f.push_back(t);
}

//�������
void keyCheck(int& p_x, int& p_y, int step,int &shoot_time)
{
	int c = GetCommand();
	DispatchCommand(c,shot,p_x,p_y,step, shoot_time);
}

void planeFun()
{
	//FlushBatchDraw();
	Plane plane;
	int p_x = 500;
	int p_y = 500;
	int step = 25;
	plane.showPlane( p_x, p_y);

	Foe foe;
	foe.setSrand();
	int foe_time = 0;	//���Ƶ��˳����ٶ�
	int shoot_type= 1;

	Boom boom;

	playBackground();
	openSound();

	while (1)
	{
		//���ڴ����Ƚ����ݼ����
		BeginBatchDraw();
		bgShow();

		boom.check(shot, f, plane);
		boom.checkPlane(f, plane);
		plane.shoot(shot);

		if (plane.life > 0)
		{
			plane.showPlane(p_x, p_y);
			keyCheck(p_x, p_y, step, shoot_type);
		}
		//��ʾ����
		setLife(plane.life);
		setScore(plane.score);
		if (plane.score >= 100 && plane.score < 200)	shoot_type = 2;
		if (plane.score >= 200 && plane.score< 500)	shoot_type = 3;
		if (plane.score >= 500)	shoot_type = 5;

		//�����������
		foe_time++;
		if (foe_time % 5 == 0)
		{
			foeFun();
		}
		
		foe.showFoe(f);
		//��ʼ�������ͼƬ��˸����
		FlushBatchDraw();
		Sleep(50);
	}
}



int main(void)
{
	cout << "main.cpp" << endl;
	initgraph(1000, 600);
	bgShow();
	planeFun();
	
	int res = _getch();
	closegraph();
	return 0;
}