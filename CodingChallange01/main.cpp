#include <iostream>
#include <GL\glew.h>
#include <GL\glut.h>
#include "Star.h"
#include "Utils.h"

#define NSTARS 500
Star stars[NSTARS];

void renderScene(void)
{
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (Star s : stars) {
		s.Show();
	}
	glutSwapBuffers();
}

void updateScene(int value) {
	for(int i = 0; i < NSTARS; i++)
		stars[i].Update();
	renderScene();
	glutTimerFunc(30, updateScene, 1);
}

void mouseMove(int x, int y)
{
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	double speed = map(y, 0.0, height, -5.0, 100.0);
	// Hopefully you do not set the vector to be empty, and accessing the first element modify
	// the static value shared among the stars
	stars[0].SetSpeed(speed);
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Coding Challenge #1: Starfield in OpenGL [All rights to Daniel Shieffman]");

	glewInit();
	
	// register callbacks
	glutPassiveMotionFunc(mouseMove);
	glutDisplayFunc(renderScene);
	glutTimerFunc(30, updateScene, 1);
	glutMainLoop();
	
	return 0;
}