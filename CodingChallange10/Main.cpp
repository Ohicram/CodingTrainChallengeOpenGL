#include <iostream>
#include <GL\glew.h>
#include <glut.h>
#include <vector>
#include "Utils.h"
#include "Cell.h"
#include "MazeGenerator.h"
using namespace std;

vector<Cell> grid;
vector<int> stack;
int current;

void initScence() {
	float w = 2.0 / GRID_SIZE;
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			grid.emplace_back(i, j, w);
		}
	}
	current = 0;
}

void renderScene(void)
{
	glClearColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT );
	for (auto c : grid)
		c.Draw();
	grid[current].Draw(8, 24, 220);
	glutSwapBuffers();
}

void updateScene(int value) {
	grid[current].Visit();
	renderScene();
	int next = findNeighbour(grid, current);
	if (next != current) {
		stack.push_back(current);
		removeWall(current, next, grid);
		current = next;
	}
	else { 
		while (stack.size() > 0) {
			current = stack.back();
			stack.pop_back();
			next = findNeighbour(grid, current);
			if (next != current)
				break;
		}
	}
	glutTimerFunc(50, updateScene, 1);
}

int main(int argc, char **argv)
{
	initScence();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowPosition(680, 80);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Coding Challenge #10: Maze Generator in OpenGL [All rights to Daniel Shieffman]");

	glewInit();
	// register callbacks
	glutDisplayFunc(renderScene);
	glutTimerFunc(250, updateScene, 1);
	glutMainLoop();

	return 0;
}