#pragma once
#define _USE_MATH_DEFINES

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

using namespace cv;
struct target;

Vec3f findCircle(Mat src);
std::vector<Point2f> findPoints(Mat src, Vec3f circle, int number);
Point2f betterPoint(Mat src, Vec3f circle, Point2f coord, float angle);
target detect(Mat src, int nPoint);
Point2f calcCircleCenter(std::vector<Point2f> Points);