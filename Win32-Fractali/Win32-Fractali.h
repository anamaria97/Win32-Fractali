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
void Draw(HDC hdc,int option)
{
	switch (option) {
	case PATRAT:
		Square(hdc, 100, 100, 200, 5);
		break;
	case CERC:
		Circle(hdc, 0, 0, 500, 10);
		break;
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