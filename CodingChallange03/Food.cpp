#include <cstdlib>
#include <iostream>
#include "Food.h"
#include <glut.h>

Food::Food()
{
}

Food::Food(int chessSqrs)
{
	cs = chessSqrs-1;
	sz = 2.0 / chessSqrs;
	SetRandomPos();
}

void Food::SetRandomPos() {
	x = round(((double)rand() / (RAND_MAX))*cs)*sz + sz / 2.0 - 1;
	y = round(((double)rand() / (RAND_MAX))*cs)*sz + sz / 2.0 - 1;
}

void Food::GetPos(float & x, float & y)
{
	x = this->x;
	y = this->y;
}


Food::~Food()
{
}

void Food::Draw() {
	glColor3f(0, 1, 0);
	auto s = sz / 2.0;
	glBegin(GL_POLYGON);
	glVertex2f(x - s, y - s);
	glVertex2f(x - s, y + s);
	glVertex2f(x + s, y + s);
	glVertex2f(x + s, y - s);
	glEnd();
}
