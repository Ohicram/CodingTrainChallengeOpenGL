#pragma once
#include <vector>


class Box
{
private:
	double x, y, z;
	double side;
public:
	Box();
	Box(double _x, double _y, double _z, double _side);
	~Box();
	void Draw();
	std::vector<Box> Generate();
	void GetCenter(double &x, double &y, double &z);
};

