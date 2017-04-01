#pragma once

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
lineEquation getLineEquation(linePoint startPoint, linePoint endPoint);
void printDistanceOfMovingObject(std::string motionImagesDir);