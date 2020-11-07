#include "font.h"

void setLife(int life)
{
	settextcolor(RED);
	TCHAR s[20];
	swprintf_s(s, _T("ÉúÃü: %d"), life);
	outtextxy(900, 20, s);
}
void setScore(int score)
{
	settextcolor(YELLOW);
	TCHAR s[20];
	swprintf_s(s, _T("·ÖÊý: %d"), score);
	outtextxy(900, 40, s);
}

