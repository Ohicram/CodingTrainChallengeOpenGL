#pragma once
#include <tuple>
static double fade(double t);
static double lerp(double t, double a, double b);
static double grad(int hash, double x, double y, double z);
static double noise(double x, double y);
static double noise(double x, double y, double z);

static const int RAND_VALUES[512] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

std::tuple<float, float, float> computeNormal(float *p1, float *p2, float *p3) {
	float v1[3] = { p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2] };
	float v2[3] = { p3[0] - p2[0], p3[1] - p2[1] ,  p3[2] - p2[2] };
	float n[3] = { v1[1] * v2[2] - v1[2] * v2[1], v1[0] * v2[2] - v1[2] * v2[0], v1[0] * v2[1] - v1[1] * v2[0] };
	float val = std::sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	return std::make_tuple(n[0] / val, n[1] / val, n[2] / val);
}

void inline computeNormal(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
	float v1[3] = { x2 - x1, y2 - y1, z2 - z1 };
	float v2[3] = { x3 - x1, y3 - y1, z3 - z1 };
	float n[3] = { v1[1] * v2[2] - v1[2] * v2[1], v1[0] * v2[2] - v1[2] * v2[0], v1[0] * v2[1] - v1[1] * v2[0] };
	float val = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	glNormal3f(n[0] / val, n[1] / val, n[2] / val);
}



static float inline map(float value, float min_range, float max_range, float min_map, float max_map) {
	float alpha = (value - min_range) / (max_range - min_range);
	return min_map + alpha * (max_map - min_map);
}

static float inline constrain(const float value, const float min, const float max) {
	return (value < min) ? min : ((value > max) ? max : value);
}

static float inline distance2(const float x1, const float y1, const float x2, const float y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

static void inline line(const float x1, const float y1, const float x2, const float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

static void inline rect(const float x, const float y, const float w, const float h) {
	auto sw = w / 2.0;
	auto sh = h / 2.0;
	glBegin(GL_POLYGON);
	glVertex2f(x - sw, y - sh);
	glVertex2f(x - sw, y + sh);
	glVertex2f(x + sw, y + sh);
	glVertex2f(x + sw, y - sh);
	glEnd();
}
static void inline rectNoFill(const float x, const float y, const float w, const float h) {
	line(x - w / 2, y + h / 2, x + w / 2, y + h / 2);
	line(x + w / 2, y + h / 2, x + w / 2, y - h / 2);
	line(x - w / 2, y - h / 2, x + w / 2, y - h / 2);
	line(x - w / 2, y - h / 2, x - w / 2, y + h / 2);
}

static float inline lerp(float a0, float a1, float w) {
	return (1.0 - w)*a0 + a1 * w;
}

float Gradient[2][2][2] = {
	{ { 0, -1 }, { -1, 0 } },
	{ { 1, 1 }, { 0, 1 } }
};
// Computes the dot product of the distance and gradient vectors.
static float dotGridGradient(int ix, int iy, float x, float y) {

	// Precomputed (or otherwise) gradient vectors at each grid node
	//extern float Gradient[IYMAX][IXMAX][2];

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx*Gradient[iy][ix][0] + dy * Gradient[iy][ix][1]);
}

static float perlin(float x, float y) {

	// Determine grid cell coordinates
	int x0 = floor(x);
	int x1 = x0 + 1;
	int y0 = floor(y);
	int y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;
	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = lerp(n0, n1, sx);
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = lerp(n0, n1, sx);
	value = lerp(ix0, ix1, sy);

	return value;
}

static double noise(double x, double y) {
	return noise(x, y, 0);
}

static double noise(double x, double y, double z) {
	int X = (int)std::floor(x) & 255,                  // FIND UNIT CUBE THAT
		Y = (int)std::floor(y) & 255,                  // CONTAINS POINT.
		Z = (int)std::floor(z) & 255;
	x -= std::floor(x);                                // FIND RELATIVE X,Y,Z
	y -= std::floor(y);                                // OF POINT IN CUBE.
	z -= std::floor(z);
	double u = fade(x),                                // COMPUTE FADE CURVES
		v = fade(y),                                // FOR EACH OF X,Y,Z.
		w = fade(z);
	int A = RAND_VALUES[X] + Y, AA = RAND_VALUES[A] + Z, AB = RAND_VALUES[A + 1] + Z,      // HASH COORDINATES OF
		B = RAND_VALUES[X + 1] + Y, BA = RAND_VALUES[B] + Z, BB = RAND_VALUES[B + 1] + Z;      // THE 8 CUBE CORNERS,

	return lerp(w, lerp(v, lerp(u, grad(RAND_VALUES[AA], x, y, z),  // AND ADD
		grad(RAND_VALUES[BA], x - 1, y, z)), // BLENDED
		lerp(u, grad(RAND_VALUES[AB], x, y - 1, z),  // RESULTS
			grad(RAND_VALUES[BB], x - 1, y - 1, z))),// FROM  8
		lerp(v, lerp(u, grad(RAND_VALUES[AA + 1], x, y, z - 1),  // CORNERS
			grad(RAND_VALUES[BA + 1], x - 1, y, z - 1)), // OF CUBE
			lerp(u, grad(RAND_VALUES[AB + 1], x, y - 1, z - 1),
				grad(RAND_VALUES[BB + 1], x - 1, y - 1, z - 1))));
}

static double fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
static double lerp(double t, double a, double b) { return a + t * (b - a); }
static double grad(int hash, double x, double y, double z) {
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h < 8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

static void ambientLighting();
static void pointLight(const float x, const float y, const float z, const float amb, const float diff, const float spec);

static void lights() {
	glEnable(GL_LIGHTING);
	ambientLighting();
	pointLight(0, 0, 10, 0, 1, .0);
}

static void ambientLighting()
{
	glEnable(GL_LIGHTING);

	double amb = .6;
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

