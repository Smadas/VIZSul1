#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <math.h>
#include <string>

#define CIRCLE_RADIUS 10
#define CIRCLE_THICKNESS 2
#define LINE_THICKNESS 2
#define POINT_RADIUS 1
#define VECTOR_COLOR cv::Scalar(0, 0, 255)
#define FONT_THICKNESS 2
#define FONT_SCALE 0.6
#define M_PI 3.14159265358979323846  /* pi */

void displayVectorY(cv::Mat *img, double direction, cv::Point centerPoint) {
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
		cv::line(*img, startPt, endPt, VECTOR_COLOR, LINE_THICKNESS, 8, 0);
		startPt.x = centerPoint.x - sin(M_PI / 4)*CIRCLE_RADIUS;
		startPt.y = centerPoint.y - cos(M_PI / 4)*CIRCLE_RADIUS;
		endPt.x = centerPoint.x + sin(M_PI / 4)*CIRCLE_RADIUS;
		endPt.y = centerPoint.y + cos(M_PI / 4)*CIRCLE_RADIUS;
		cv::line(*img, startPt, endPt, VECTOR_COLOR, LINE_THICKNESS, 8, 0);
	}
	else//kamera vzad pohyb
	{
		cv::circle(*img, centerPoint, POINT_RADIUS, VECTOR_COLOR, CIRCLE_THICKNESS, 8, 0);
	}
	//font = cv2.FONT_HERSHEY_SIMPLEX;
	std::string vectorStr;
	vectorStr = std::to_string(abs(direction)) + " cm";
	cv::Point textPoint = centerPoint;
	textPoint.x = textPoint.x + CIRCLE_RADIUS * 2;
	textPoint.y = textPoint.y + CIRCLE_RADIUS - 4;
	cv::putText(*img, vectorStr, textPoint, cv::FONT_HERSHEY_SIMPLEX, FONT_SCALE, VECTOR_COLOR, FONT_THICKNESS, 8, false);
}
void displayVectorXZ(cv::Mat *img, float x, float y, double angle, cv::Point centerPoint)
{
	//put text
	std::string vectorStr;
	float distance = sqrt(pow(x,2) + pow(y,2));
	angle = 360 - angle + 270;
	if (angle >= 360) {
		angle -= 360;
	}

	vectorStr = std::to_string(distance) + " cm; " + std::to_string(abs(angle)) + " deg";

	cv::Point textPoint = centerPoint;
	textPoint.x = textPoint.x + CIRCLE_RADIUS * 2;
	textPoint.y = textPoint.y + CIRCLE_RADIUS - 4;
	cv::putText(*img, vectorStr, textPoint, cv::FONT_HERSHEY_SIMPLEX, FONT_SCALE, VECTOR_COLOR, FONT_THICKNESS, 8, false);
	cv::Point startPt;
	cv::Point endPt;

	//put arrow
	endPt.x = centerPoint.x + sin(angle / 180 * M_PI) * 10;
	endPt.y = centerPoint.y + cos(angle / 180 * M_PI) * 10;
	centerPoint.x = centerPoint.x - sin(angle / 180 * M_PI) * 10;
	centerPoint.y = centerPoint.y - cos(angle / 180 * M_PI) * 10;
	if (distance > 0.2)
	{
		cv::arrowedLine(*img, centerPoint, endPt, VECTOR_COLOR, LINE_THICKNESS, 8, 0, 0.5);
	}
	
}