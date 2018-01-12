#include <iostream>
#include <GL\glew.h>
#include <glut.h>
#include "Utils.h"
#include "Box.h"
#include <vector>
#include <mutex>

using namespace std;
double tx, ty, tz;
int angle = 0;
vector<Box> sponge, spongeBuffer;

void renderScene(void)
{
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(tx, ty, tz);
	glRotated(angle++, 1.0, 0.5, .5);
	glTranslated(-tx, -ty, -tz);
	for (auto b : sponge) {
		b.Draw();
		}
	glPopMatrix();
	glutSwapBuffers();
}

void updateScene(int value) {
	renderScene();
	glutTimerFunc(30, updateScene, 1);
}

void mousePressed(int button, int state, int x, int y) {
	if (button == 0 && state == 0) {
		spongeBuffer.clear();
			for (Box b : sponge) {
				vector<Box> ite = b.Generate();
				for (Box i : ite) {
					spongeBuffer.push_back(i);
				}
			}
		sponge.clear();
		sponge = spongeBuffer;
	}
}

int main(int argc, char **argv)
{
	tx = ty = 0;
	tz = -3.5;
	sponge.push_back(Box{ tx, ty, tz, 2});
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Coding Challenge #2: Menger Sponge Fractalin OpenGL [All rights to Daniel Shieffman]");

	glewInit();
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1, 1, -1, 1, 1, 8);
	lights();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutMouseFunc(mousePressed);
	glutDisplayFunc(renderScene);
	glutTimerFunc(30, updateScene, 1);
	glutMainLoop();

	return 0;
}