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
void Hexagon(HDC, int, int, int, int, int, int, int);
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
	case HEXAGON:
		Hexagon(hdc, 190, 10, 20, 340, 360, 340, 5);
	}


}


void Intersection(int aX, int aY, int bX, int bY, int mX, int mY, int nX, int nY, int *M, int *N) {
	int kX = bX - aX;
	int kY = bY - aY;
	int lX = mX - nX;
	int lY = mY - nY;

	int r1 = kY * aX - kX * aY;
	int r2 = lY * mX - lX * mY;

	int det = (kX * lY - kY * lX);

	*M = (r2 * kX - r1 * lX) / det;
	*N = (kY * r2 - r1 * lY) / det;
}

void Hexagon(HDC hdc, int aX, int aY, int bX, int bY, int cX, int cY, int iter) {
	//if (sqrt((bX - aX) * (bX - aX) + (bY - aY) * (bY - aY)) < minDist) 
	if (iter == 0)
		return;
	int mX, mY, nX, nY, pX, pY;
	//Centrul de greutate
	int gX, gY;
	gX = (aX + bX + cX) / 3;
	gY = (aY + bY + cY) / 3;
	//triunghi intors
	mX = 2 * gX - aX;
	mY = 2 * gY - aY;
	nX = 2 * gX - bX;
	nY = 2 * gY - bY;
	pX = 2 * gX - cX;
	pY = 2 * gY - cY;
	//Noile puncte
	int ab1X, ab1Y, ab2X, ab2Y, ac1X, ac1Y, ac2X, ac2Y, bc1X, bc1Y, bc2X, bc2Y;
	Intersection(aX, aY, bX, bY, pX, pY, nX, nY, &ab1X, &ab1Y);
	Intersection(aX, aY, bX, bY, pX, pY, mX, mY, &ab2X, &ab2Y);
	Intersection(aX, aY, cX, cY, pX, pY, nX, nY, &ac1X, &ac1Y);
	Intersection(aX, aY, cX, cY, mX, mY, nX, nY, &ac2X, &ac2Y);
	Intersection(bX, bY, cX, cY, pX, pY, mX, mY, &bc1X, &bc1Y);
	Intersection(bX, bY, cX, cY, mX, mY, nX, nY, &bc2X, &bc2Y);

	// Desen
	
		MoveToEx(hdc, aX, aY, NULL);
		LineTo(hdc, bX, bY);
		MoveToEx(hdc, bX, bY, NULL);
		LineTo(hdc, cX, cY);
		MoveToEx(hdc, cX, cY, NULL);
		LineTo(hdc, aX, aY);
	

	MoveToEx(hdc, mX, mY, NULL);
	LineTo(hdc, nX, nY);
	MoveToEx(hdc, nX, nY, NULL);
	LineTo(hdc, pX, pY);
	MoveToEx(hdc, pX, pY, NULL);
	LineTo(hdc, mX, mY);

	Sleep(10);

	Hexagon(hdc, aX, aY, ab1X, ab1Y, ac1X, ac1Y, iter - 1);
	Hexagon(hdc, bX, bY, ab2X, ab2Y, bc1X, bc1Y, iter - 1);
	Hexagon(hdc, cX, cY, ac2X, ac2Y, bc2X, bc2Y, iter - 1);

	Hexagon(hdc, mX, mY, bc1X, bc1Y, bc2X, bc2Y, iter - 1);
	Hexagon(hdc, nX, nY, ac1X, ac1Y, ac2X, ac2Y, iter - 1);
	Hexagon(hdc, pX, pY, ab1X, ab1Y, ab2X, ab2Y, iter - 1);
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