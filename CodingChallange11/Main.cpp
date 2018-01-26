#include <iostream>
#include <GL\glew.h>
#include <glut.h>
#include <vector>
#include <tuple>
#include "Utils.h"

using namespace std;
int NCell = 30;
float ***grid;
float ***norm;
float iter{};
float col1[3]{ 0, 0.5, 0.5 };
float col2[3]{0.96, 0, 0.63};

void setupNormals() {
	float cs = 2.0 / NCell;
	float str = -1 + cs / 2;
	//grid = new float[10];
	norm = new float**[NCell];
	for (int i = (NCell - 1); i >= 0; i--) {
		norm[i] = new float*[NCell];
		for (int j = (NCell - 1); j >= 0; j--) {
			if (i == 0 || j == 0 || i == (NCell - 1) || j == (NCell - 1)) {
				norm[i][j] = new float[3]{ 0, 0, 1 };
				continue;
			}
			auto n1 = computeNormal(grid[i - 1][j - 1], grid[i][j], grid[i - 1][j]);
			auto n2 = computeNormal(grid[i - 1][j], grid[i][j], grid[i][j + 1]);
			auto n3 = computeNormal(grid[i][j + 1], grid[i][j], grid[i + 1][j + 1]);
			auto n4 = computeNormal(grid[i + 1][j], grid[i][j], grid[i + 1][j + 1]);
			auto n5 = computeNormal(grid[i + 1][j], grid[i][j], grid[i][j - 1]);
			auto n6 = computeNormal(grid[i - 1][j - 1], grid[i][j], grid[i][j - 1]);
			auto avgx = (get<0>(n1) + get<0>(n2) + get<0>(n3) + get<0>(n4) + get<0>(n5) + get<0>(n6)) / 6.0;
			auto avgy = (get<1>(n1) + get<1>(n2) + get<1>(n3) + get<1>(n4) + get<1>(n5) + get<1>(n6)) / 6.0;
			auto avgz = (get<2>(n1) + get<2>(n2) + get<2>(n3) + get<2>(n4) + get<2>(n5) + get<2>(n6)) / 6.0;
			float nor = sqrt(avgx*avgx + avgy * avgy + avgz * avgz);
			nor = avgz < 0 ? -nor : nor;
			norm[i][j] = new float[3]{ (float)avgx / nor, (float)avgy / nor, (float)avgz / nor };
		}
	}
}

void updateNormals() {
	for (int i = 0; i < NCell; i++) {
		for (int j = 0; j < NCell; j++) {
			if (i == 0 || j == 0 || i == (NCell - 1) || j == (NCell - 1)) {
				continue;
			}
			auto n1 = computeNormal(grid[i - 1][j - 1], grid[i][j], grid[i - 1][j]);
			auto n2 = computeNormal(grid[i - 1][j], grid[i][j], grid[i][j + 1]);
			auto n3 = computeNormal(grid[i][j + 1], grid[i][j], grid[i + 1][j + 1]);
			auto n4 = computeNormal(grid[i + 1][j], grid[i][j], grid[i + 1][j + 1]);
			auto n5 = computeNormal(grid[i + 1][j], grid[i][j], grid[i][j - 1]);
			auto n6 = computeNormal(grid[i - 1][j - 1], grid[i][j], grid[i][j - 1]);
			auto avgx = (get<0>(n1) + get<0>(n2) + get<0>(n3) + get<0>(n4) + get<0>(n5) + get<0>(n6)) / 6.0;
			auto avgy = (get<1>(n1) + get<1>(n2) + get<1>(n3) + get<1>(n4) + get<1>(n5) + get<1>(n6)) / 6.0;
			auto avgz = (get<2>(n1) + get<2>(n2) + get<2>(n3) + get<2>(n4) + get<2>(n5) + get<2>(n6)) / 6.0;
			float nor = sqrt(avgx*avgx + avgy * avgy + avgz * avgz);
			nor = avgz < 0 ? -nor : nor;
			norm[i][j][0] = (float)avgx / nor;
			norm[i][j][1] = (float)avgy / nor;
			norm[i][j][2] = (float)avgz / nor;
		}
	}
}

void setupTerrain() {
	float cs = 2.0 / NCell;
	float str = -1 + cs / 2;
	//grid = new float[10];
	grid = new float**[NCell];
	for (int i = 0; i < NCell; i++) {
		grid[i] = new float*[NCell];
		for (int j = 0; j < NCell; j++) {
			grid[i][j] = new float[3]{str + i*cs, str + j*cs, (float)noise(i*0.25,j*0.25)*0.25f};
		}
	}
	setupNormals();
}

void updateTerrain() {

	for (int j = 0; j < NCell-1; j++) {
		for (int i = 0; i < NCell; i++) {
			grid[i][j][2] = grid[i][j+1][2];
		}
	}
	for (int i = 0; i < NCell; i++) {
		grid[i][NCell-1][2] = (float)noise(i*0.25,iter*0.05,iter*0.002)*0.2f;
	}
	updateNormals();
	iter+=0.75;
}

void drawTerrain() {
	glPushMatrix();
	glRotated(60, 1, 0, 0);
	//glTranslated(0, 0, 0.5);
	glEnable(GL_COLOR_MATERIAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 0.5f, 0.5f);
	for (int i = 0; i < NCell-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < NCell; j++) {
			auto alpha = grid[i][j][2] / 0.2f;
			glColor3f(lerp(col1[0], col2[0], alpha), lerp(col1[1], col2[1], alpha), lerp(col1[2], col2[2], alpha));
			glNormal3f(norm[i][j][0], norm[i][j][1], norm[i][j][2]);
			glVertex3f(grid[i][j][0], grid[i][j][1], grid[i][j][2]);
			alpha = grid[i+1][j][2] / 0.2f;
			glColor3f(lerp(col1[0], col2[0], alpha), lerp(col1[1], col2[1], alpha), lerp(col1[2], col2[2], alpha));
			glNormal3f(norm[i+1][j][0], norm[i+1][j][1], norm[i+1][j][2]);
			glVertex3f(grid[i+1][j][0], grid[i+1][j][1], grid[i+1][j][2]);
		}
		glEnd();
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 0);
	for (int i = 0; i < NCell - 1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int j = 0; j < NCell; j++) {
			auto alpha = 1- grid[i][j][2] / 0.2f;
			glColor4f(alpha, alpha, 0, 0.25);
			glNormal3f(norm[i][j][0], norm[i][j][1], norm[i][j][2]);
			glVertex3f(grid[i][j][0], grid[i][j][1], grid[i][j][2]);
			alpha = 1- grid[i+1][j][2] / 0.2f;
			glColor4f(alpha, alpha, 0, 0.25);
			glNormal3f(norm[i + 1][j][0], norm[i + 1][j][1], norm[i + 1][j][2]);
			glVertex3f(grid[i + 1][j][0], grid[i + 1][j][1], grid[i + 1][j][2]);
		}
		glEnd();
	}
	glPopMatrix();
}

void renderScene(void)
{
	glClearColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	drawTerrain();
	updateTerrain();
	glutSwapBuffers();
}

void updateScene(int value) {
	renderScene();
	glutTimerFunc(30, updateScene, 1);
}

int main(int argc, char **argv)
{
	setupTerrain();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(680, 80);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Coding Challenge #11: Terrain Generation with Perlin Noise in OpenGL [All rights to Daniel Shieffman]");

	glewInit();
	lights();
	glMatrixMode(GL_PROJECTION);
	glFrustum(-3, 3, -3, 3, 0, 2);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	// register callbacks
	glutDisplayFunc(renderScene);
	glutTimerFunc(30, updateScene, 1);
	glutMainLoop();

	return 0;
}