#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>

#define CIRCLE_RADIUS 10
#define CIRCLE_THICKNESS 2
#define LINE_THICKNESS 1
#define POINT_RADIUS 1
#define VECTOR_COLOR cv::Scalar(0, 0, 255)
# define M_PI           3.14159265358979323846  /* pi */

void displayVectorY(cv::Mat *img, int direction, cv::Point centerPoint) {
	cv::circle(*img, centerPoint, CIRCLE_RADIUS, VECTOR_COLOR, CIRCLE_THICKNESS, 8, 0);
	if (direction < 0)//kamera vpred pohyb
	{
		//draw x
		cv::Point startPt;
		cv::Point endPt;
		startPt.x = centerPoint.x - sin(M_PI / 4)*CIRCLE_RADIUS;
		startPt.y = centerPoint.y + cos(M_PI / 4)*CIRCLE_RADIUS;
		endPt.x = centerPoint.x + sin(M_PI / 4)*CIRCLE_RADIUS;
		endPt.y = centerPoint.y - cos(M_PI / 4)*CIRCLE_RADIUS;
		cv::line(*img, startPt, endPt, cv::Scalar(0, 0, 255), LINE_THICKNESS, 8, 0);
		startPt.x = centerPoint.x - sin(M_PI / 4)*CIRCLE_RADIUS;
		startPt.y = centerPoint.y - cos(M_PI / 4)*CIRCLE_RADIUS;
		endPt.x = centerPoint.x + sin(M_PI / 4)*CIRCLE_RADIUS;
		endPt.y = centerPoint.y + cos(M_PI / 4)*CIRCLE_RADIUS;
		cv::line(*img, startPt, endPt, cv::Scalar(0, 0, 255), LINE_THICKNESS, 8, 0);
	}
	else//kamera vzad pohyb
	{
		cv::circle(*img, centerPoint, POINT_RADIUS, cv::Scalar(0, 0, 255), CIRCLE_THICKNESS, 8, 0);
	}
}
