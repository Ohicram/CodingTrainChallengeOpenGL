#include "Box.h"
#include <glut.h>
#include <vector>

using namespace std;
Box::Box() :
	x{ 0.0 }, y{ 0.0 }, z{ 0.0 }, side{ 1 }
{
}


Box::Box(double _x, double _y, double _z, double _side):
	x{_x}, y{_y}, z{_z}, side{_side}
{
}


Box::~Box()
{
}

void Box::Draw() {
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor4f(1.0f, 0.83f, 0.3f, 0.5f);
	//glLoadIdentity();
	glTranslated(x, y, z);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	auto size = side / 2.0;
	//FACCE Z
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3d(-size, -size, -size);
	glVertex3d(size, -size, -size);
	glVertex3d(size, size, -size);
	glVertex3d(-size, size, -size);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3d(-size, -size, +size);
	glVertex3d(size, -size, +size);
	glVertex3d(size, size, +size);
	glVertex3d(-size, size, +size);
	glEnd();
	//FACCE X
	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3d(size, -size, -size);
	glVertex3d(size, -size, size);
	glVertex3d(size, size, size);
	glVertex3d(size, size, -size);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3d(-size, -size, -size);
	glVertex3d(-size, -size, size);
	glVertex3d(-size, size, size);
	glVertex3d(-size, size, -size);
	glEnd();
	//FACCE Y
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3d(-size, size, -size);
	glVertex3d(size, size, -size);
	glVertex3d(size, size, size);
	glVertex3d(-size, size, size);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3d(-size, -size, -size);
	glVertex3d(size, -size, -size);
	glVertex3d(size, -size, size);
	glVertex3d(-size, -size, size);
	glEnd();
	glPopMatrix();
}

vector<Box> Box::Generate() {
	vector<Box> boxes;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				for (int k = -1; k < 2; k++) {
					if ((abs(i) + abs(j) + abs(k)) > 1){
						double nS = side / 3.0;
						Box b{ x + i * nS, y + j * nS, z + k * nS, nS };
						boxes.push_back(b);
					}
				}
			}
		}
	return boxes;
}

void Box::GetCenter(double & x, double & y, double & z)
{
	x = this->x;
	y = this->y;
	z = this->z;
}
