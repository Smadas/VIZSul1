#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "DetectTarget.h"
#include "readImagesFromDirectory.h"
#include "detectMotionY.h"

lineEquation calibrateAxisY(std::string calibImagesDir){
	lineEquation calibLineEquation;
	calibLineEquation.K = 0;
	calibLineEquation.Q = 0;
	std::vector<cv::Mat> readImages = readImgFiles(calibImagesDir);
	std::cout << "calib img num " << readImages.size() << std::endl;
	if (readImages.size() < 2)
	{
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

double getObjectMovementY()
{
	
	return 0;
}

lineEquation getLineEquation(linePoint startPoint, linePoint endPoint){
	lineEquation lineEquationC;
	lineEquationC.K = 0;
	lineEquationC.Q = 0;
	if ((endPoint.x - startPoint.x) == 0)
	{
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
	for (int imgCount = 0; imgCount < readImages.size(); imgCount += 15)
	{
		cv::Vec3f startPoint3 = findCircle(readImages.at(imgCount));
		double objDist = getObjectDistanceY(widthDistanceDependency, startPoint3[2], CALIB_CIRCLE_DIAMETER / 2);
		std::cout << "Camera distance from target! " << objDist << std::endl;
		imshow("Display window", readImages.at(imgCount));
		waitKey(20);
	}
}