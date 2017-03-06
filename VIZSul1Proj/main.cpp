#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace cv;
using namespace std;

/*vector<string> get_all_files_names_within_folder(string folder)
{
	vector<string> names;
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}*/

int main()
{
	//test branch
	Mat image;
	Point lineStart;
	Point lineEnd;
	lineEnd.x = 20;
	lineEnd.y = 20;
	lineStart.x = 100;
	lineStart.y = 100;
	//image = imread(, IMREAD_COLOR); // Read the file
	image = imread("Autobus.bmp", IMREAD_COLOR);

	//read directory
	/*std::vector<string> names;
	WIN32_FIND_DATA fd;
	LPCWSTR search_path = L"captureVidX\\*.bmp*";
	int fileCounter = 0;
	HANDLE hFind = FindFirstFile(search_path, &fd);
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
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	else{
		std::cout << "Could not open folder!" << std::endl;
	}*/

	vector<string> names;
	WIN32_FIND_DATAA fd;
	LPCSTR search_path = "captureVidX\\*.bmp*";
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


	if (!image.data){ // Check for invalid input
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	line(image, lineStart, lineEnd, Scalar(0, 255, 0), 5, 8, 0);
	imshow("Display window", image); // Show our image inside it.
									 //zapisanie obrazka so suboru
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);
	try {
		imwrite("vystup.png", image, compression_params);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
		return 1;
	}

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}