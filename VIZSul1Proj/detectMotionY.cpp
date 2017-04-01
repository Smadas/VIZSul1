#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

#include "DetectTarget.h"
#include "readImagesFromDirectory.h"
#include "detectMotionY.h"
#include "opticalFlowLucasKanade.h"


struct target {
	std::vector<Point2f> points;
	Point2f center;
} tar1;

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
	cv::Vec3f radius = findCircle(img);//fitEllipse, minEnclosingCircle
	distance = widthDistanceDependency.K*objectWidthCm / radius[2]/2.0 + widthDistanceDependency.Q;
	return distance;
}

double getObjectDistanceY(lineEquation widthDistanceDependency, std::vector<cv::Point2f> circlePoints, double objectWidthCm) {
	double distance;
	//cv::Vec3f diameter = findCircle(img);//fitEllipse, minEnclosingCircle
	Point2f circleCenter;
	float radius;
	minEnclosingCircle(circlePoints, circleCenter, radius);
	distance = widthDistanceDependency.K*objectWidthCm / radius + widthDistanceDependency.Q;
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
		cv::Vec3f radius = findCircle(readImages.at(imgCount));//fitEllipse, minEnclosingCircle
		double objDist = getObjectDistanceY(widthDistanceDependency, radius[2], CALIB_CIRCLE_DIAMETER / 2);
		std::cout << "Camera distance from target! " << objDist << std::endl;
		cv::imshow("Display window", readImages.at(imgCount));
		cv::waitKey(20);
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
		cv::Vec3f radius = findCircle(readImages.at(imgCount));//fitEllipse, minEnclosingCircle
		objDist = getObjectDistanceY(widthDistanceDependency, radius[2], CALIB_CIRCLE_DIAMETER / 2);
		double movement = getObjectMotionY(&objDist, &objDistPrev);
		std::cout << "Camera distance movement toward target! " << movement << std::endl;
		cv::imshow("Display window", readImages.at(imgCount));
		cv::waitKey(20);
	}
}

void printMovementVectorLengthYoptflow(std::string motionImagesDir)
{
	lineEquation widthDistanceDependency = calibrateAxisY("calibY\\");
	std::vector<cv::Mat> readImages = readImgFiles(motionImagesDir);
	cv::Mat gray, prevGray, image, frame;
	std::vector<cv::Point2f> points[2];
	cv::namedWindow("Display window", 1);
	double objDist = 0;
	double objDistPrev = 0;

	// Detect good points to track
	frame = readImages.at(0);
	target tar1;
	tar1 = detect(frame, 15);
	points[0] = tar1.points;

	for (int imgCount = 0; imgCount < readImages.size(); imgCount += 15) {
		frame = readImages.at(imgCount);
		if (frame.empty())
			break;
		frame.copyTo(image);
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		computeOpticalFlow(&gray, &prevGray, &points[0], &points[1]);
		//show points
		if (!points[0].empty())
		{
			size_t i, k;
			for (i = 0; i < points[1].size(); i++)
			{
				circle(image, points[1][i], 3, cv::Scalar(0, 255, 0), -1, 8);
			}
		}
		cv::Vec3f diameter = findCircle(readImages.at(imgCount));//fitEllipse, minEnclosingCircle
		objDist = getObjectDistanceY(widthDistanceDependency, points[1], CALIB_CIRCLE_DIAMETER / 2);
		double movement = getObjectMotionY(&objDist, &objDistPrev);
		std::cout << "Camera distance movement toward target! " << movement << std::endl;
		imshow("Display window", image);
		cv::waitKey(100);
	}
}