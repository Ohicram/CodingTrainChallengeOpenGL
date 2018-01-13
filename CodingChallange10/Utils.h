#pragma once

static float inline map(float value, float min_range, float max_range, float min_map, float max_map) {
	float alpha = (value - min_range) / (max_range - min_range);
	return min_map + alpha * (max_map - min_map);
}

static float inline constrain(const float value, const float min, const float max) {
	return (value < min) ? min : ((value > max) ? max : value);
}

static float inline distance2(const float x1, const float y1, const float x2, const float y2) {
	return (x1 - x2)*(x1 - x2) + (y1-y2)*(y1-y2);
}

static void inline line(const float x1, const float y1, const float x2, const float y2) {
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

static void inline rect(const float x, const float y, const float w, const float h){
	auto sw = w / 2.0;
	auto sh = h / 2.0;
	glBegin(GL_POLYGON);
		glVertex2f(x - sw, y - sh);
		glVertex2f(x - sw, y + sh);
		glVertex2f(x + sw, y + sh);
		glVertex2f(x + sw, y - sh);
	glEnd();
}