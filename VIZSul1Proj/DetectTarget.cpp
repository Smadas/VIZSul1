#include "detectTarget.h"

using namespace cv;
using namespace std;

struct target {
	vector<Point2f> points;
	Point2f center;
} tar;

target detect(Mat src, int nPoint) {
	// Function to detect specified number of evenly distributed points around target and get target center
	// Mat src - image
	// int nPoints - number of points
	// Output - struct {vector<Point2f> points; Point2f center}

	Vec3f circle;
	vector<Point2f> points;
	Point2f center;

	// Get circle center and radius [x,y,radius]
	circle = findCircle(src);

	// Get specified points on circle
	points = findPoints(src, circle, nPoint);

	// Get precise circle center
	center = calcCircleCenter(points);

	tar.points = points;
	tar.center = Point(circle[0], circle[1]);

	return tar;

}

Vec3f findCircle(Mat src) {
	// Find circle in picture using HoughCircles method
	// input - Mat picture
	// output - Vec3f [x,y,radius] of a target circle

	vector<Vec3f> circles;
	Mat gray;
	Vec3f c = (0, 0, 0);
	Vec3b colour;

	cvtColor(src, gray, COLOR_BGR2GRAY);
	medianBlur(gray, gray, 5);

	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16,
		100, 30, 40, 70 // change the last two parameters
						// (min_radius & max_radius) to detect larger circles
	);
	Mat pic = src.clone();
	// Remove all other circles
	for (size_t i = 0; i < circles.size(); i++) {

		c = circles[i];
		colour = src.at<Vec3b>(c[1], c[0]);
		
		// Zobraz kruh
		/*Point center(cvRound(c[0]), cvRound(c[1]));
		int radius = cvRound(c[2]);
		cv::circle(pic, center, radius, Scalar(0, 0, 255), 2, 8);
		imshow("Display window", pic);
		waitKey(0);*/

		// compare centre pixel with [<180>,<120-255>,<220-255>] BGR 
		if ((colour[0] < 220) && (colour[1] > 100) && (colour[2] > 180)) {
			return (circles[i]);
		}

	}

	

	// If no good circle detected, return 0
	return c;

}

vector<Point2f> findPoints(Mat src, Vec3f circle, int number) {
	// Evenly distributes points around the circle and return specified points
	// Mat src - picture
	// int number - number of detecting points
	// vector<Vec2i> - output points on real target

	float cx = circle[0];
	float cy = circle[1];
	float r = circle[2] + 5;
	float angleDiff = M_PI * 2 / number; // angle difference between 2 points
	float angle;
	vector<Point2f> output[1];
	Point2f coord;

	// Get angles of points
	for (size_t i = 0; i < number; i++) {

		angle = i * angleDiff;

		coord.x = cx + r*sin(angle);
		coord.y = cy + r*cos(angle);

		coord = betterPoint(src, circle, coord, angle);

		output[0].push_back(coord);

	}

	return output[0];
}

Point2f betterPoint(Mat src, Vec3f circle, Point2f coord, float angle) {
	// Change points to match color of target

	float cx = circle[0];
	float cy = circle[1];
	float r = circle[2];

	float x = coord.x;
	float y = coord.y;

	Vec3b colour;
	Point2f betterCoord;

	Mat pic = src.clone();

	// posuvaj sa po malych kuskoch smerom k stredu a zistuj, ci je farba v rozmedzi farebnej skaly targetu
	while (1) {

		x = x - sin(angle)*0.2;
		y = y - cos(angle)*0.2;

		betterCoord.x = x;
		betterCoord.y = y;
		colour = src.at<Vec3b>(y, x);

		// Zobraz posunutie
		/*cv::circle(pic, betterCoord, 3, Scalar(0, 0, 255), -1, 8);
		imshow("Display window", pic);
		waitKey(20);*/

		if ((colour[0] < 240) && (colour[1] > 100) && (colour[2] > 180)) {
			break;
		}


	}

	return betterCoord;

}

Point2f calcCircleCenter(vector<Point2f> Points) {
	// Find center of target using 3 detected evenly distributed points

	float cx, cy;
	int n, n2;
	Point2f p1, p2, p3, center = (0, 0);

	// Ak nie je dostatok bodov, ukonci sa
	if (Points.size() < 3) {
		return center;
	}

	// Vyber 3 body rovnomerne rozdelene
	n = Points.size();
	p1 = Points[0];
	n2 = floor(n / 3);

	if (fmod(n, 3) == 2) {
		p2 = Points[n2 + 1];
		p3 = Points[n2 * 2 + 1];
	}
	else
	{
		p2 = Points[n2];
		p3 = Points[n2 * 2];
	}

	// Vypocet stredu kruznice
	float ma = (p2.y - p1.y) / (p2.x - p1.x);
	float mb = (p3.y - p2.y) / (p3.x - p2.x);
	center.x = (ma * mb * (p1.y - p3.y) + mb * (p1.x - p2.x) - ma * (p2.x + p3.x)) / (2 * (mb - ma));
	center.y = (-1 / ma) * (center.x - (p1.x + p2.x) / 2) + (p1.y + p2.y) / 2;
	return center;

}


void vectorParam(vector<Point2f> points) {
	// Calculate angle and magnitude of vectors

	int size = points.size();
	int dx;
	int dy;

	for (size_t i = 0; i < size; i++) {
		dx = points[0][i];
	}



}
