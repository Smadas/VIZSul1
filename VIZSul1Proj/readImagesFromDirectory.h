#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

std::vector<std::string> getImageFileNames(std::string imagesDirectory);
std::vector<cv::Mat> readImgFiles(std::string imagesDirectory, bool invert);
int showImagesFromDirectory(std::string imagesDirectory);