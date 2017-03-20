#include "opticalFlowLucasKanade.h"
#include "DetectTarget.h"

struct target {
	std::vector<Point2f> points;
	Point2f center;
};

int main()
{
	//if (0 != showOpticalFlow()) {
	//}
	//return 0;

	// Detect object
	Mat src = imread("TestImage.bmp", IMREAD_COLOR);
	int nPoint = 8;
	Point2f coord;
	target tar;

	tar = detect(src, nPoint);

	// Display dots
	for (size_t i = 0; i < tar.points.size(); i++) {
		coord = tar.points[i];
		cv::circle(src, coord, 3, Scalar(0, 0, 255), -1, 8);
	}
	cv::circle(src, tar.center, 3, Scalar(0, 0, 255), -1, 8);
	imshow("Display window", src);
	waitKey();
		

}