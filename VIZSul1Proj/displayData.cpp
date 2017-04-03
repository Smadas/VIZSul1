#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

#define CIRCLE_RADIUS 5
#define POINT_RADIUS 1

void displayVectorY(cv::Mat *img, int direction, cv::Point centerPoint) {
	cv::circle(*img, centerPoint, CIRCLE_RADIUS, cv::Scalar(0, 0, 255), 1, 8, 0);
	if (direction > 0)//kamera vzad pohyb
	{
		//draw x
		cv::Point startPt;
		cv::Point endPt;
		startPt.x = 0;
		startPt.y = 0;
		endPt.x = 0;
		endPt.y = 0;
		cv::line(*img, startPt, endPt, cv::Scalar(0, 0, 255), 1, 8, 0);
		startPt.x = 0;
		startPt.y = 0;
		endPt.x = 0;
		endPt.y = 0;
		cv::line(*img, startPt, endPt, cv::Scalar(0, 0, 255), 1, 8, 0);
	}
	else//kamera vpred pohyb
	{
		cv::circle(*img, centerPoint, POINT_RADIUS, cv::Scalar(0, 0, 255), 1, 8, 0);
	}
}