#pragma once
static void ambientLighting();
static void pointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec);

static float inline map(float value, float min_range, float max_range, float min_map, float max_map) {
	float alpha = (value - min_range) / (max_range - min_range);
	return min_map + alpha * (max_map - min_map);
}

static void lights() {
	glPushMatrix(); // push under the stack the current modeview matrix
	glLoadIdentity(); // reset all transformations draw your light
	glEnable(GL_LIGHTING);
	ambientLighting();
	pointLight(0, 0, 10, 0, 1, .0);
	glPopMatrix(); // pop the last pushed modelview matrix to restore it as the current modelview matrix.

}

static void ambientLighting()
{
	glEnable(GL_LIGHTING);

	double amb = .5;
	GLfloat global_ambient[] = { amb,amb,amb, .5 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

static void pointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec)
{
	glEnable(GL_LIGHTING);


	GLfloat light_ambient[] = { amb,amb,amb, 1 };
	GLfloat light_diffuse[] = { diff, diff, diff,1 };
	GLfloat light_specular[] = { spec, spec, spec, 1 };

	GLfloat light_position[] = { x,y,z, 0.0 };
	GLfloat light_direction[] = { -x,-y,-z };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_position);

	glEnable(GL_LIGHT0); //enable the light after setting the properties

}