#pragma onc
static float inline map(float value, float min_range, float max_range, float min_map, float max_map) {
	float alpha = (value - min_range) / (max_range - min_range);
	return min_map + alpha * (max_map - min_map);
}

static void drawCube(double size) {
	auto side = size / 2.0;
	//FACCE Z
	glBegin(GL_POLYGON);
	glVertex3d(-side, -side, -side);
	glVertex3d(side, -side, -side);
	glVertex3d(side, side, -side);
	glVertex3d(-side, side, -side);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(-side, -side, +side);
	glVertex3d(side, -side, +side);
	glVertex3d(side, side, +side);
	glVertex3d(-side, side, +side);
	glEnd();
	//FACCE X
	glBegin(GL_POLYGON);
	glVertex3d(side, -side, -side);
	glVertex3d(side, -side, side);
	glVertex3d(side, side, side);
	glVertex3d(side, side, -side);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(-side, -side, -side);
	glVertex3d(-side, -side, side);
	glVertex3d(-side, side, side);
	glVertex3d(-side, side, -side);
	glEnd();
	//FACCE Y
	glBegin(GL_POLYGON);
	glVertex3d(-side, side, -side);
	glVertex3d(side, side, -side);
	glVertex3d(side, side, side);
	glVertex3d(-side, side, side);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3d(-side, -side, -side);
	glVertex3d(side, -side, -side);
	glVertex3d(side, -side, side);
	glVertex3d(-side, -side, side);
	glEnd();

}