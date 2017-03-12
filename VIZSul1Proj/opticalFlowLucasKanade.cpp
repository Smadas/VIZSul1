#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <ctype.h>

#include "readImagesFromDirectory.h"

//using namespace cv;

int computeOpticalFlow(cv::Mat *gray, cv::Mat *prevGray, std::vector<cv::Point2f> *points, std::vector<cv::Point2f> *prevPoints) {
	cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
	cv::Size subPixWinSize(10, 10), winSize(31, 31);

	const int MAX_COUNT = 500;

	if (!points->empty()){
		std::vector<uchar> status;
		std::vector<float> err;
		if (prevGray->empty())
			gray->copyTo(*prevGray);
		calcOpticalFlowPyrLK(*prevGray, *gray, *points, *prevPoints, status, err, winSize,
			3, termcrit, 0, 0.001);
		std::cout << "prevPoints" << prevPoints->size() << std::endl;
	}

	std::swap(prevPoints, points);
	cv::swap(prevGray, gray);

	return 0;
}

int showOpticalFlow() {
	//read image files
	std::vector<cv::Mat> readImages = readImgFiles("captureVidX\\");

	cv::namedWindow("LK Demo", 1);

	cv::Mat gray, prevGray, image, frame;
	cv::Point2f myPoint;
	std::vector<cv::Point2f> points[2];

	//put pobject points
	myPoint.x = 434;
	myPoint.y = 171;
	points[0].push_back(myPoint);
	myPoint.x = 486;
	myPoint.y = 226;
	points[0].push_back(myPoint);
	myPoint.x = 447;
	myPoint.y = 273;
	points[0].push_back(myPoint);
	myPoint.x = 411;
	myPoint.y = 272;
	points[0].push_back(myPoint);
	myPoint.x = 378;
	myPoint.y = 222;
	points[0].push_back(myPoint);
	myPoint.x = 394;
	myPoint.y = 188;
	points[0].push_back(myPoint);
	myPoint.x = 473;
	myPoint.y = 190;
	points[0].push_back(myPoint);
	myPoint.x = 471;
	myPoint.y = 258;
	points[0].push_back(myPoint);
	myPoint.x = 390;
	myPoint.y = 255;
	points[0].push_back(myPoint);
		/*
		434 171
		486 226
		447 273
		411 272
		378 222
		394 188
		473 190
		471 258
		390 255
			*/


	for (int i = 0; i < readImages.size(); i++){
		frame = readImages.at(i);
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

		cv::imshow("LK Demo", image);
		cv::waitKey(20);
	}

	return 0;
}