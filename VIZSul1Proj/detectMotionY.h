#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#include "DetectTarget.h"
#include "readImagesFromDirectory.h"
#include "detectMotionY.h"

#define CALIB_CIRCLE_DIAMETER 10.0 //centimeters
#define CALIB_CAMERA_TARGET_DIST 85.0 //centimeters
#define CALIB_CAMERA_MOVEMENT 18.0 //centimeters, backwards

struct lineEquation {
	double K = 0;
	double Q = 0;
};
struct linePoint {
	double x = 0;
	double y = 0;
};
lineEquation calibrateAxisY(std::string calibImagesDir);
double getObjectDistanceY(lineEquation widthDistanceDependency, double objectWidthPix, double objectWidthCm);
double getObjectDistanceY(lineEquation widthDistanceDependency, cv::Mat img, double objectWidthCm);
double getObjectDistanceY(lineEquation widthDistanceDependency, std::vector<cv::Point2f> circlePoints, double objectWidthCm);
double getObjectMotionY(double *objectDist, double *objectDistPrev);
lineEquation getLineEquation(linePoint startPoint, linePoint endPoint);
void printDistanceOfMovingObject(std::string motionImagesDir);
void printMovementVectorLengthY(std::string motionImagesDir);