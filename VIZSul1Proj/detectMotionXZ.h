#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <stdlib.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

struct vectorP {
	float dx;
	float dy;
	float angle;
};


vectorP vectorParam(Point2f coord1, Point2f coord2);
Point2f getObjectmotionXZ(std::vector<Point2f> points1, vector<Point2f> points2);

