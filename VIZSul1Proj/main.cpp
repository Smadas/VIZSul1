#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>


using namespace cv;
using namespace std;

Mat applyLaplace(Mat src) {
	Mat  src_gray, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";

	//int c;

	/// Remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Apply Laplace function
	Mat abs_dst;

	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	return abs_dst;

}

int main(int argc, const char** argv)
{

	// add your file name
	VideoCapture cap(0);// "internetExperiment.wmv");//"MOV_0011.mp4");


	Mat flow, frame;
	// some faster than mat image container
	UMat  flowUmat, prevgray;

	for (;;)
	{

		bool Is = cap.grab();
		if (Is == false) {
			// if video capture failed
			cout << "Video Capture Fail" << endl;
			break;
		}
		else {



			Mat img;
			Mat original;
			Mat laplace;

			// capture frame from video file
			cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
			resize(img, img, Size(640, 480));

			// save original for later
			img.copyTo(original);

			// apply laplace operator
			laplace = applyLaplace(img);

			// just make current frame gray
			cvtColor(img, img, COLOR_BGR2GRAY);


			// For all optical flow you need a sequence of images.. Or at least 2 of them. Previous                           //and current frame
			//if there is no current frame
			// go to this part and fill previous frame
			//else {
			// img.copyTo(prevgray);
			//   }
			// if previous frame is not empty.. There is a picture of previous frame. Do some                                  //optical flow alg. 

			if (prevgray.empty() == false) {

				// calculate optical flow 
				calcOpticalFlowFarneback(prevgray, img, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
				// copy Umat container to standard Mat

				flowUmat.copyTo(flow);


				// By y += 5, x += 5 you can specify the grid 
				for (int y = 0; y < original.rows; y += 5) {
					for (int x = 0; x < original.cols; x += 5)
					{
						// get the flow from y, x position * 10 for better visibility
						const Point2f flowatxy = flow.at<Point2f>(y, x) * 10;
						// draw line at flow direction
						line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(255, 0, 0));
						// draw initial point
						circle(original, Point(x, y), 1, Scalar(0, 0, 0), -1);


					}

				}

				// draw the results
				namedWindow("prew", WINDOW_AUTOSIZE);
				imshow("prew", original);

				namedWindow("laplacian", WINDOW_AUTOSIZE);
				imshow("laplacian", laplace);

				// fill previous image again
				img.copyTo(prevgray);

			}
			else {

				// fill previous image in case prevgray.empty() == true
				img.copyTo(prevgray);

			}


			int key1 = waitKey(20);

		}
	}
}