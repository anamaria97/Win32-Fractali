#pragma once
#define SFERT 1/4

#include "resource.h"
#include <math.h>

void draw(HDC hdc,int x,int y,int dist,int minDist)
{
	if (dist < minDist) return;
	draw(hdc, x - dist*SFERT, y - dist*SFERT, dist/2, minDist);
	draw(hdc, x+dist - dist*SFERT, y+dist - dist*SFERT, dist / 2, minDist);
	draw(hdc, x- dist*SFERT, y + dist - dist*SFERT, dist / 2, minDist);
	draw(hdc, x + dist - dist*SFERT, y - dist*SFERT, dist / 2, minDist);
	Sleep(50);
	Rectangle(hdc, x, y, x + dist, y + dist);
}

void circle(HDC hdc,int x, int y,int dist,int minDist)
{
	Sleep(10);
	Ellipse(hdc, x, y, x+dist , y+dist);
	//Ellipse(hdc, x+x/2, y+y/2, x+dist/2, y+dist/2);
	if (dist < minDist) return;

	circle(hdc,x + dist / 4, y , dist / 2, minDist);
	circle(hdc, x , y + dist / 4, dist / 2, minDist);
	circle(hdc, x+dist/4, y + dist/2, dist / 2, minDist);
	circle(hdc, x + dist / 2, y + dist / 4, dist / 2, minDist);
//	circle(hdc, x +dist - dist*SFERT, y+dist - dist*SFERT, dist / 4, minDist);
//	circle(hdc, x + dist - dist*SFERT, y + dist - dist*SFERT, dist / 2, minDist);
//	circle(hdc, x - dist*SFERT, y + dist - dist*SFERT, dist / 2, minDist);
	//circle(hdc, x + dist - dist*SFERT, y + dist - dist*SFERT, dist / 2, minDist);
	
	//	Rectangle(hdc, x, y, x + dist, y + dist);

//	Ellipse(hdc,100,100,400,400);
}