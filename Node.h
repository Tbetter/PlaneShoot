#pragma once

class Node
{
public:
	
	bool operator==(Node t)
	{
		if ((x > t.x - 25 && x <= t.x + 25) && (y > t.y - 30 && y <= t.y + 30))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int x;
	int y;
	int dir;	//1:right 2:left
};
