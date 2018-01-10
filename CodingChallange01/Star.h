#pragma once
#include <cstdlib>
#include <iostream>
#include <GL\glut.h>

//static double speed;

class Star
{
protected:
	static double speed;
	void init();
	double oz;
public:
	double x, y, z;
	Star();
	Star(double _x, double _y);
	~Star();
	void Show();
	void Update();
	void SetSpeed(double s);
};

std::ostream &operator << (std::ostream &os, const Star &s);

