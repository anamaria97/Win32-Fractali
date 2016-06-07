#pragma once
#define SFERT 1/4

#include "resource.h"
#include <math.h>
#define PATRAT 1
#define CERC 2
#define TRIUNGHI 3
#define HEXAGON 4
void Square(HDC, int, int , int,int);
void Circle(HDC, int, int, int, int);
void Triangle(HDC,int,int,int,int,int,int,int);
void Draw(HDC hdc,int option)
{
	switch (option) {
	case PATRAT:
		Square(hdc, 100, 100, 200, 5);
		break;
	case CERC:
		Circle(hdc, 0, 0, 500, 10);
		break;
	case TRIUNGHI:
		Triangle(hdc, 190, 10, 20, 340, 360, 340,8);
	}


}


void Square(HDC hdc,int x,int y,int dist,int minDist)
{
	if (dist < minDist) return;
	Square(hdc, x - dist*SFERT, y - dist*SFERT, dist/2, minDist);
	Square(hdc, x+dist - dist*SFERT, y+dist - dist*SFERT, dist / 2, minDist);
	Square(hdc, x- dist*SFERT, y + dist - dist*SFERT, dist / 2, minDist);
	Square(hdc, x + dist - dist*SFERT, y - dist*SFERT, dist / 2, minDist);
	Sleep(50);
	Rectangle(hdc, x, y, x + dist, y + dist);
}

void Circle(HDC hdc,int x, int y,int dist,int minDist)
{
	Sleep(10);
	Ellipse(hdc, x, y, x+dist , y+dist);
	if (dist < minDist) return;

	Circle(hdc,x + dist / 4, y , dist / 2, minDist);
	Circle(hdc, x , y + dist / 4, dist / 2, minDist);
	Circle(hdc, x+dist/4, y + dist/2, dist / 2, minDist);
	Circle(hdc, x + dist / 2, y + dist / 4, dist / 2, minDist);
}
void Triangle(HDC hdc,int aX,int aY,int bX,int bY,int cX,int cY,int count)
{
	if (count == 0)
		return;
	int mX, mY, nX, nY, pX, pY;
	mX = abs(aX + bX) / 2;
	mY = abs(aY + bY) / 2;

	nX = abs(aX + cX) / 2;
	nY = abs(aY + cY) / 2;

	pX = abs(bX + cX) / 2;
	pY = abs(bY + cY) / 2;
	MoveToEx(hdc, aX, aY, NULL);
	LineTo(hdc, bX, bY);
	MoveToEx(hdc, bX, bY, NULL);
	LineTo(hdc, cX, cY);
	MoveToEx(hdc, aX, aY, NULL);
	LineTo(hdc, cX, cY);
	Sleep(10);
	Triangle(hdc, aX, aY, mX, mY, nX, nY, count - 1);
	Triangle(hdc, mX, mY, bX, bY, pX, pY, count - 1);
	Triangle(hdc, nX, nY, pX, pY, cX, cY, count - 1);
}