#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <string>
#include <chrono>


using namespace cv;
using namespace std;
using namespace std::chrono;

void saveFrame(Mat src) {
	//cas
	time_t rawtime;
	struct tm*timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	std::string myFileName;
	milliseconds ms = duration_cast< milliseconds >(
		system_clock::now().time_since_epoch()
		);
	std::ostringstream mlss;
	mlss << ms.count();
	std::string milli_str = mlss.str();
	myFileName = "captureVid\\" + milli_str + ".bmp";
	//zapisanie obrazka do suboru
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {

		imwrite(myFileName, src, compression_params);

		cout << myFileName << endl;
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return;
	}

}

void captureVideoAsImages(int cameraID) {
	cv::UMat prevgray;

	// add your file name
	VideoCapture cap(cameraID);
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
			// capture frame from video file
			cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

			//save frame to file
			saveFrame(img);



			namedWindow("orig", WINDOW_AUTOSIZE);
			imshow("orig", img);

			// fill previous image again
			img.copyTo(prevgray);


			int key1 = waitKey(100);
		}
	}
}