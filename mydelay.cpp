#include "mydelay.h"

void delay_msec(int msec)
{
	clock_t now = clock();
	while (clock() - now < msec);
}