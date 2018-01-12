#pragma once
#include <vector>
#include "Food.h"

enum class Direction{LEFT, RIGHT, UP, DOWN};

struct Point2D
{
	float x;
	float y;
};

class Snake
{
private:
	bool alive{ true };
	float x, y;
	std::vector<Point2D> body;
	Direction d;
	float speed, sqSize;
public:
	Snake();
	Snake(int s);
	~Snake();
	void testCollisions();
	void Draw();
	void Update();
	void Eat(Food &f);
	void Steer(Direction newDir);
};
