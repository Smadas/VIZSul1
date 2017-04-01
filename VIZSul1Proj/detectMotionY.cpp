#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#include "DetectTarget.h"
#include "readImagesFromDirectory.h"
#include "detectMotionY.h"

lineEquation calibrateAxisY(std::string calibImagesDir){
	lineEquation calibLineEquation;
	calibLineEquation.K = 0;
	calibLineEquation.Q = 0;
	std::vector<cv::Mat> readImages = readImgFiles(calibImagesDir);
	std::cout << "calib img num " << readImages.size() << std::endl;
	if (readImages.size() < 2){
		std::cout << "Failed to read calibration images!" << std::endl;
		return calibLineEquation;
	}
	cv::Vec3f startPoint3 = findCircle(readImages.at(0));
	cv::Vec3f endPoint3 = findCircle(readImages.at(1));
	linePoint startPoint;
	linePoint endPoint;
	startPoint.x = CALIB_CIRCLE_DIAMETER / 2.0 / startPoint3[2];
	startPoint.y = CALIB_CAMERA_TARGET_DIST;
	endPoint.x = CALIB_CIRCLE_DIAMETER / 2.0 / endPoint3[2];
	endPoint.y = CALIB_CAMERA_TARGET_DIST + CALIB_CAMERA_MOVEMENT;
	calibLineEquation = getLineEquation(startPoint, endPoint);
	return calibLineEquation;
}

double getObjectDistanceY(lineEquation widthDistanceDependency, double objectWidthPix, double objectWidthCm) {
	double distance;
	distance = widthDistanceDependency.K*objectWidthCm / objectWidthPix + widthDistanceDependency.Q;
	return distance;
}

double getObjectDistanceY(lineEquation widthDistanceDependency, cv::Mat img, double objectWidthCm) {
	double distance;
	cv::Vec3f diameter = findCircle(img);//fitEllipse, minEnclosingCircle
	distance = widthDistanceDependency.K*objectWidthCm / diameter[2]/ 2 + widthDistanceDependency.Q;
	return distance;
}

double getObjectDistanceY(lineEquation widthDistanceDependency, std::vector<cv::Point2f> circlePoints, double objectWidthCm) {
	double distance;
	//cv::Vec3f diameter = findCircle(img);//fitEllipse, minEnclosingCircle
	Point2f circleCenter;
	float radius;
	minEnclosingCircle(circlePoints, circleCenter, radius);
	distance = widthDistanceDependency.K*objectWidthCm / radius / 2 + widthDistanceDependency.Q;
	return distance;
}

double getObjectMotionY(double *objectDist, double *objectDistPrev) {
	double motion = 0;
	motion = *objectDist - *objectDistPrev;
	*objectDistPrev = *objectDist;
	return motion;
}

lineEquation getLineEquation(linePoint startPoint, linePoint endPoint){
	lineEquation lineEquationC;
	lineEquationC.K = 0;
	lineEquationC.Q = 0;
	if ((endPoint.x - startPoint.x) == 0){
		std::cout << "Error, division by zero!" << std::endl;
		return lineEquationC;
	}
	lineEquationC.K = (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);
	lineEquationC.Q = startPoint.y - startPoint.x*lineEquationC.K;
	return lineEquationC;
}

void printDistanceOfMovingObject(std::string motionImagesDir) {
	lineEquation widthDistanceDependency = calibrateAxisY("calibY\\");
	std::vector<cv::Mat> readImages = readImgFiles(motionImagesDir);
	cv::namedWindow("Display window", 1);
	for (int imgCount = 0; imgCount < readImages.size(); imgCount += 15){
		cv::Vec3f diameter = findCircle(readImages.at(imgCount));//fitEllipse, minEnclosingCircle
		double objDist = getObjectDistanceY(widthDistanceDependency, diameter[2], CALIB_CIRCLE_DIAMETER / 2);
		std::cout << "Camera distance from target! " << objDist << std::endl;
		imshow("Display window", readImages.at(imgCount));
		waitKey(20);
	}
}

void printMovementVectorLengthY(std::string motionImagesDir)
{
	lineEquation widthDistanceDependency = calibrateAxisY("calibY\\");
	std::vector<cv::Mat> readImages = readImgFiles(motionImagesDir);
	cv::namedWindow("Display window", 1);
	double objDist = 0;
	double objDistPrev = 0;

	for (int imgCount = 0; imgCount < readImages.size(); imgCount += 15) {
		cv::Vec3f diameter = findCircle(readImages.at(imgCount));//fitEllipse, minEnclosingCircle
		objDist = getObjectDistanceY(widthDistanceDependency, diameter[2], CALIB_CIRCLE_DIAMETER / 2);
		double movement = getObjectMotionY(&objDist, &objDistPrev);
		std::cout << "Camera distance movement toward target! " << movement << std::endl;
		imshow("Display window", readImages.at(imgCount));
		waitKey(20);
	}
}

