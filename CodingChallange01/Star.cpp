#include "Star.h"
#include <cstdlib>
#include <iostream>
#include <GL\glut.h>
#include "Utils.h"

double Star::speed = 0;

Star::Star(double _x, double _y) : x{_x}, y{_y}, z{8}
{
}

Star::Star()
{
	init();
}

Star::~Star()
{
}

void Star::init() {
	x = -1 + ((double)rand() / (RAND_MAX))*2.0;
	y = -1 + ((double)rand() / (RAND_MAX))*2.0;
	z = ((double)rand() / (RAND_MAX));
	oz = z;
}

std::ostream &operator << (std::ostream &os, const Star &s) {
	os << s.x << "," << s.y;
	return os;
}


void Star::Update() {
	oz = z;
	z -= 0.15 * (speed/100.0); // Values go toward zero
	if (z <= 0) {
		init();
		z = oz = 1;
	}
}

void Star::Show() {
	if (!glIsEnabled(GL_POINT_SMOOTH))
		glEnable(GL_POINT_SMOOTH);
	glPointSize(map(z, 0, 1, 5, 0.5));
	glColor3f(1, 1, 1);

	glBegin(GL_POINTS);
		glVertex2f(x/z, y/z);
	glEnd();

	glBegin(GL_LINES);
		glVertex2f(x / z, y / z);
		glVertex2f(x / oz, y / oz);
	glEnd();
}

void Star::SetSpeed(double s) {
	this->speed = s;
}
