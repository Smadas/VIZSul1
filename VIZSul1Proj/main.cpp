#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace cv;
using namespace std;

std::vector<string> getImageFileNames(std::string imagesDirectory) {
	std::vector<string> names;
	WIN32_FIND_DATAA fd;
	//LPCSTR search_path = "captureVidX\\*.bmp*";
	LPCSTR search_path = imagesDirectory.c_str();
	int fileCounter = 0;
	HANDLE hFind = FindFirstFileA(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				//names.push_back(fd.cFileName);
				fileCounter++;
				std::cout << fileCounter << std::endl;
				std::cout << fd.cFileName << std::endl;
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	else {
		std::cout << "Could not open folder!" << std::endl;
	}

	return names;
}

std::vector<cv::Mat> readImgFiles(std::string imagesDirectory) {

}

int main()
{
	Mat image;
	Point lineStart;
	Point lineEnd;
	lineEnd.x = 20;
	lineEnd.y = 20;
	lineStart.x = 100;
	lineStart.y = 100;
	std::string imgFileName;
	std::string imgFilesDirectory = "captureVidX\\";
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.

	//read directory
	std::vector<string> imgFileNames;
	imgFileNames = getImageFileNames("captureVidX\\*.bmp*");
	int imgFilesNumber = imgFileNames.size();
	
	//show all images from directory
	for (int imageCount = 1; imageCount < imgFilesNumber; imageCount++) {
		imgFileName = imgFilesDirectory + imgFileNames.at(imageCount);
		image = cv::imread(imgFileName, IMREAD_COLOR);
		if (!image.data) { // Check for invalid input
			cout << "Could not open or find the image" << std::endl;
			return -1;
		}

		
		cv::imshow("Display window", image); // Show our image inside it.
		//line(image, lineStart, lineEnd, Scalar(0, 255, 0), 5, 8, 0);
		//imshow("Display window", image); // Show our image inside it.
										 //zapisanie obrazka so suboru
		/*vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		try {
			imwrite("vystup.png", image, compression_params);
		}
		catch (runtime_error& ex) {
			fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
			return 1;
		}*/

		int key1 = cv::waitKey(20);
	}
	

	cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}