#include "pMove.h"


pMove::pMove(int x1, int y1, int x2, int y2)
{
	mFromX = x1;
	mFromY = y1;
	mToX = x2;
	mToY = y2;
	mPoint = 0;
}

pMove::pMove(int x1, int y1, int x2, int y2, int point)
{
	mFromX = x1;
	mFromY = y1;
	mToX = x2;
	mToY = y2;
	mPoint = point;
}

pMove::pMove()
{
	mFromX = 0;
	mFromY = 0;
	mToX = 0;
	mToY = 0;
	mPoint = 0;
}

pMove::~pMove()
{
}

void pMove::setPoint(int a)
{
	mPoint = a;
}

void pMove::addPoint(int a)
{
	mPoint +=  a;
}


