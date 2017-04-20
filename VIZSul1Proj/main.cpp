#include "opticalFlowLucasKanade.h"
#include "DetectTarget.h"
#include "readImagesFromDirectory.h"
#include "detectMotionY.h"
#include "detectMotionXZ.h"
#include "displayData.h"

//int main() {
//
//	//printDistanceOfMovingObject("captureVidY\\");
//	//printMovementVectorLengthY("captureVidY\\");
//	printMovementVectorLengthYoptflow("captureVidY\\");
//	waitKey(0);
//	return 0;
//}

struct target {
	std::vector<Point2f> points;
	Point2f center;
};

int main()
{
	int nPoint = 15;
	Point2f coord, coord2, xz;
	target tar;
	cv::Mat gray, prevGray, image, frame;
	cv::Point2f myPoint;
	std::vector<cv::Point2f> points2[2];
	double objDist = 0;
	double objDistPrev = 0;

	// ------------------------------------------------------------------------------------------------------

	// Read images
	std::vector<cv::Mat> readImages = readImgFiles("captureVidX\\",true);

	// Detect good points to track
	frame = readImages.at(0);
	tar = detect(frame, nPoint);
	points2[0] = tar.points;

	// Calibrate Y target
	lineEquation widthDistanceDependency = calibrateAxisY("calibY\\");

	// Read images one by one
	for (int i = 0; i < readImages.size(); i += 15) {
		frame = readImages.at(i);
		if (frame.empty())
			break;

		// Compute optical flow
		frame.copyTo(image);
		cvtColor(image, gray, cv::COLOR_BGR2GRAY);
		computeOpticalFlow(&gray, &prevGray, &points2[0], &points2[1]);

		// Display points
		if (!points2[0].empty())
		{
			size_t i;
			for (i = 0; i < points2[0].size(); i++)
			{
				circle(image, points2[0][i], 3, cv::Scalar(0, 255, 0), -1, 8);
			}
		}

		// Calculate Y axis
		cv::Vec3f diameter = findCircle(readImages.at(i));
		objDist = getObjectDistanceY(widthDistanceDependency, points2[0], CALIB_CIRCLE_DIAMETER / 2);
		double movement = getObjectMotionY(&objDist, &objDistPrev);
		if (abs(movement) > Y_TRESHOLD)
		{
			std::cout << "Camera Movement Y : " << movement << std::endl;
			displayVectorY(&image, movement, Point(30, 30));
		}
		else
		{
			// Calculate XZ axis
			vectorP angleXZ = vectorParam(points2[0][0], points2[1][0]);
			xz = getObjectmotionXZ(points2[0], points2[1]);
			if (xz.x < -0.1) {
				std::cout << "Camera Movement Right : " << -xz.x << std::endl;
			}
			else if (xz.x > 0.1) {
				std::cout << "Camera Movement Left : " << xz.x << std::endl;
			}
			if (xz.y < -0.1) {
				std::cout << "Camera Movement Down : " << -xz.y << std::endl;
			}
			else if (xz.y > 0.1) {
				std::cout << "Camera Movement Up : " << xz.y << std::endl;
			}
			displayVectorXZ(&image, xz.x, xz.y, angleXZ.angle, Point(30,30));
		}

		// Display image
		if (i > 0) {
			imshow("Display window", image);
			waitKey(300);
		}


	}

	waitKey(0);
	return 0;
}

