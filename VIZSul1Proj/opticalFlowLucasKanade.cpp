#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <ctype.h>

#include "readImagesFromDirectory.h"

using namespace cv;

int computeOpticalFlow(cv::Mat gray, cv::Mat prevGray, std::vector<cv::Point2f> points, std::vector<cv::Point2f> prevPoints) {
	cv::TermCriteria termcrit(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 20, 0.03);
	Size subPixWinSize(10, 10), winSize(31, 31);

	const int MAX_COUNT = 500;

	if (!points.empty()){
		std::vector<uchar> status;
		std::vector<float> err;
		if (prevGray.empty())
			gray.copyTo(prevGray);
		calcOpticalFlowPyrLK(prevGray, gray, points, prevPoints, status, err, winSize,
			3, termcrit, 0, 0.001);
	}

	std::swap(prevPoints, points);
	cv::swap(prevGray, gray);

	return 0;
}

int showOpticalFlow() {
	//read image files
	std::vector<cv::Mat> readImages = readImgFiles("captureVidX\\");
	

	namedWindow("LK Demo", 1);

	Mat gray, prevGray, image, frame;
	std::vector<Point2f> points[2];

	for (int i = 0; i < readImages.size(); i++){
		std::cout << "autobus" << std::endl;
		frame = readImages.at(i);
		if (frame.empty())
			break;

		frame.copyTo(image);
		cvtColor(image, gray, COLOR_BGR2GRAY);

		computeOpticalFlow(gray, prevGray, points[0], points[1]);
		if (!points[0].empty())
		{
			size_t i, k;
			for (i = k = 0; i < points[1].size(); i++)
			{
				circle(image, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
			}
		}

		cv::imshow("LK Demo", image);
		cv::waitKey(20);
	}

	return 0;
}