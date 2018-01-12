#include "Snake.h"
#include "Utils.h"
#include <glut.h>


Snake::Snake() : speed {0.1f}, d {Direction::RIGHT}
{
}

Snake::Snake(int s)
{
	sqSize = 2.0 / s;
	x = sqSize / 2.0;
	y = sqSize / 2.0;
	speed = sqSize;
}

Snake::~Snake()
{
}

void Snake::testCollisions()
{
	for (auto c : body) {
		if (distance2(c.x, c.y, x, y) < sqSize*sqSize)
			alive = false;
	}
}

void Snake::Draw()
{
	if(alive)
		glColor3f(1, 1, 1);
	else
		glColor3f(1, 0, 0);
	auto s = sqSize / 2.0;
	glBegin(GL_POLYGON);
		glVertex2f(x - s, y- s);
		glVertex2f(x - s, y + s);
		glVertex2f(x + s, y + s);
		glVertex2f(x + s, y - s);
	glEnd();
	for (auto p : body) {
		glBegin(GL_POLYGON);
		glVertex2f(p.x - s, p.y - s);
		glVertex2f(p.x - s, p.y + s);
		glVertex2f(p.x + s, p.y + s);
		glVertex2f(p.x + s, p.y - s);
		glEnd();
	}
}

void Snake::Update()
{
	if (!alive)
		return;
	if (body.size() > 0) {
		for (int i = 0; i < (body.size() - 1); i++) {
			body[i].x = body[i + 1].x;
			body[i].y = body[i + 1].y;
		}
		body[body.size() - 1].x = x;
		body[body.size() - 1].y = y;
	}
	switch (d) {
		case Direction::LEFT:
			x -= speed; break;
		case Direction::RIGHT:
			x += speed; break;
		case Direction::DOWN:
			y -= speed; break;
		case Direction::UP:
			y += speed; break;
	}
	//x = constrain(x, sqSize / 2 - 1, 1 - sqSize / 2);
	//y = constrain(y, sqSize / 2 - 1, 1 - sqSize / 2);
	x = (x > (1 - sqSize / 2)) ? -1 + sqSize / 2 : (x < (sqSize / 2 - 1) ? 1 - sqSize / 2 : x);
	y = (y > (1 - sqSize / 2)) ? -1 + sqSize / 2 : (y < (sqSize / 2 - 1) ? 1 - sqSize / 2 : y);
	testCollisions();
}

void Snake::Eat(Food & f)
{
	Point2D pos;
	f.GetPos(pos.x, pos.y);
	if (distance2(pos.x, pos.y, x, y) < sqSize*sqSize) {
		f.SetRandomPos();
		body.push_back(pos);
	}
}

void Snake::Steer(Direction newDir)
{
	d = newDir;
}


