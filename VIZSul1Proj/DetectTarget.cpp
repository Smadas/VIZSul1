#include "detectTarget.h"

using namespace cv;
using namespace std;

Vec3f findCircle(Mat src) {
	// input - Mat picture
	// output - Vec3f [x,y,radius] of a target circle

	vector<Vec3f> circles;
	Mat gray;
	Vec3f c;
	Vec3b colour;

	cvtColor(src, gray, COLOR_BGR2GRAY);
	medianBlur(gray, gray, 5);

	HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16,
		100, 30, 40, 70 // change the last two parameters
						// (min_radius & max_radius) to detect larger circles
	);

	// Remove all other circles
	for (size_t i = 0; i < circles.size(); i++) {

		c = circles[i];
		colour = src.at<Vec3b>(c[1], c[0]);
		
		// compare centre pixel with [<120-220>,<240-255>,<240-255>] BGR (real colour is [180 255 255])
		if ((colour[0] > 120) && (colour[0] < 220) && (colour[1] > 240) && (colour[2] > 240)) {
			return (circles[i]);
		}

	}

	// If no good circle detected, return 0
	return 0;

}

