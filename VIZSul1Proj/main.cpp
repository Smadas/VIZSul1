#include "opticalFlowLucasKanade.h"
#include "DetectTarget.h"
#include "readImagesFromDirectory.h"

struct target {
	std::vector<Point2f> points;
	Point2f center;
};

int main()
{
	/*if (0 != showOpticalFlow()) {
	}
	return 0;*/

	int nPoint = 20;
	Point2f coord, coord2;
	target tar;
	cv::Mat gray, prevGray, image, frame;
	cv::Point2f myPoint;
	std::vector<cv::Point2f> points2[2];

	// ------------------------------------------------------------------------------------------------------

	// Read images
	std::vector<cv::Mat> readImages = readImgFiles("captureVidX\\");

	// Read images one by one
	for (int i = 0; i < readImages.size(); i += 10) {
		frame = readImages.at(i);
		if (frame.empty())
			break;


		// Detect good points to track
		tar = detect(frame, nPoint);
		points2[0] = tar.points;


		// Compute optical flow
		frame.copyTo(image);
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		computeOpticalFlow(&gray, &prevGray, &points2[0], &points2[1]);

		/*// Display dots
		for (size_t i = 0; i < tar.points.size(); i++) {
		coord = tar.points[i];
		cv::circle(image, coord, 3, Scalar(0, 0, 255), -1, 8);
		}*/
		// Display vectors
		for (size_t i = 0; i < tar.points.size(); i++) {
			coord = points2[0][i];
			coord2 = points2[1][i];
			cv::arrowedLine(image, coord, coord2, Scalar(0, 0, 255), 2, 8);
		}
		cv::circle(image, tar.center, 3, Scalar(0, 0, 255), -1, 8);
		imshow("Display window", image);
		waitKey(150);

	}

	waitKey(0);
}