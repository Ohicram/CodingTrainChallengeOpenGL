#include <iostream>
#include <GL\glew.h>
#include <glut.h>
#include "Utils.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

int chessSize = 32;
Snake s{ chessSize };
Food f{ chessSize };

void renderScene(void)
{
	glClearColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT );
	s.Draw();
	f.Draw();
	glutSwapBuffers();
}

void updateScene(int value) {
	s.Update();
	s.Eat(f);
	renderScene();
	glutTimerFunc(150, updateScene, 1);
}

void keyPressed(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		s.Steer(Direction::UP); break;
	case GLUT_KEY_DOWN:
		s.Steer(Direction::DOWN); break;
	case GLUT_KEY_LEFT:
		s.Steer(Direction::LEFT); break;
	case GLUT_KEY_RIGHT:
		s.Steer(Direction::RIGHT); break;
	default:
		break;
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Coding Challenge #3: The Snake Game OpenGL [All rights to Daniel Shieffman]");

	glewInit();
	// register callbacks
	glutSpecialFunc(keyPressed);
	glutDisplayFunc(renderScene);
	glutTimerFunc(30, updateScene, 1);
	glutMainLoop();

	return 0;
}