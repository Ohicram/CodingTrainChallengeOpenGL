#include <glut.h>
#include "Cell.h"
#include "Utils.h"

Cell::Cell()
{
}

Cell::Cell(int i, int j, float w)
{
	side = w;
	x = i * w + w / 2.0 - 1;
	y = j * w + w / 2.0 - 1;
}

Cell::~Cell()
{
}

void Cell::Draw() {
	auto s = side / 2.0;
	if (visited) {
		glColor3f(0.75, 0.06, 0.18);
		rect(x, y, side, side);
	}
	glColor3f(1, 1, 1);
	if (walls[0])
		line(x - s, y + s, x + s, y + s);
	if (walls[1])
		line(x + s, y + s, x + s, y - s);
	if (walls[2])
		line(x - s, y - s, x + s, y - s);
	if (walls[3])
		line(x - s, y - s, x - s, y + s);
}

void Cell::Draw(unsigned char r, unsigned char g, unsigned char b)
{
	auto s = side / 2.0;
	glColor3f(r/255.0, g/255.0, b/255.0);
	rect(x, y, side, side);
	glColor3f(1, 1, 1);
	if (walls[0])
		line(x - s, y + s, x + s, y + s);
	if (walls[1])
		line(x + s, y + s, x + s, y - s);
	if (walls[2])
		line(x - s, y - s, x + s, y - s);
	if (walls[3])
		line(x - s, y - s, x - s, y + s);
}

void Cell::Visit()
{
	visited = true;
}

void Cell::RemoveTop()
{
	walls[0] = false;
}

void Cell::RemoveRight()
{
	walls[1] = false;
}

void Cell::RemoveBottom()
{
	walls[2] = false;
}

void Cell::RemoveLeft()
{
	walls[3] = false;
}

bool Cell::IsVisited()
{
	return visited;
}
