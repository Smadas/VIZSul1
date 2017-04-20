#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace cv;
using namespace std;

#define IMG_TYPE "*.bmp*"

std::vector<std::string> getImageFileNames(std::string imagesDirectory) {
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
				//std::cout << fileCounter << std::endl;
				//std::cout << fd.cFileName << std::endl;
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}
	else {
		std::cout << "Could not open folder!" << std::endl;
		return{};
	}

	return names;
}

std::vector<cv::Mat> readImgFiles(std::string imagesDirectory, bool invert) {
	Mat image;
	std::vector<cv::Mat> readImages;
	std::string imgFileName;
	std::string imgFilesDirectory = imagesDirectory;

	//read image file names
	std::vector<string> imgFileNames;
	imgFileNames = getImageFileNames(imagesDirectory + IMG_TYPE);
	int imgFilesNumber = imgFileNames.size();
	if (imgFilesNumber == 0) {
		std::cout << "Error reading image files!" << std::endl;
		return{};
	}

	//read files
	if (invert == false) {
		for (int imageCount = 0; imageCount < imgFilesNumber; imageCount++) {
			imgFileName = imgFilesDirectory + imgFileNames.at(imageCount);
			image = cv::imread(imgFileName, IMREAD_COLOR);
			if (!image.data) { // Check for invalid input
				cout << "Could not open or find the image!" << std::endl;
				return{};
			}
			else {
				readImages.push_back(image);
			}
		}
	}
	else {
		for (int imageCount = imgFilesNumber-1; imageCount > 0; imageCount--) {
			imgFileName = imgFilesDirectory + imgFileNames.at(imageCount);
			image = cv::imread(imgFileName, IMREAD_COLOR);
			if (!image.data) { // Check for invalid input
				cout << "Could not open or find the image!" << std::endl;
				return{};
			}
			else {
				readImages.push_back(image);
			}
		}
	}
	return readImages;
}

int showImagesFromDirectory(std::string imagesDirectory) {
	Mat image;
	int numImages = 0;
	std::vector<cv::Mat> readImages;
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.

													//show all images from directory
	readImages = readImgFiles(imagesDirectory, false);
	numImages = readImages.size();
	if (numImages == 0) {
		std::cout << "Could not read images!" << std::endl;
		return 0;
	}
	for (int imageCount = 0; imageCount < numImages; imageCount++) {
		image = readImages.at(imageCount);
		cv::imshow("Display window", image); // Show our image inside it.
		int key1 = cv::waitKey(20);
	}

	cv::waitKey(0); // Wait for a keystroke in the window
	return 0;
}