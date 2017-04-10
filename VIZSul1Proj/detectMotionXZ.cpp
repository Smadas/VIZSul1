#include "detectMotionXZ.h"


vectorP vectorParam(Point2f coord1, Point2f coord2) {
	// Calculate angle and magnitude of vectors

	vectorP v;

	v.dx = coord1.x - coord2.x;
	v.dy = coord1.y - coord2.y;

	v.angle = atan2(v.dy, v.dx);

	if (v.angle < 0) {
		v.angle = 180 + 180 + v.angle * 180 / M_PI;
	}
	else {
		v.angle = v.angle * 180 / M_PI;
	}

	return v;
}

Point2f getObjectmotionXZ(vector<Point2f> points1, vector<Point2f> points2) {

	int pointsNumber = points1.size();
	vectorP v;
	float angle = 0;
	float x = 0, y = 0;
	Point2f point;

	for (int i = 0; i < pointsNumber; i++) {

		v = vectorParam(points1[i], points2[i]);
		x = x + v.dx;
		y = y + v.dy;
		angle = angle + v.angle;
	}

	point.x = x / pointsNumber;
	point.y = y / pointsNumber;

	return point;

}