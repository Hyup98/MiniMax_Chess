#pragma once
class pMove
{
public:
	pMove(int x1,int y1, int x2, int y2);
	pMove(int x1, int y1, int x2, int y2, int point);
	pMove();
	~pMove();
	int mFromX;
	int mFromY;
	int mToX;
	int mToY;
	int mPoint;
	void setPoint(int a);
	void addPoint(int a);
};

