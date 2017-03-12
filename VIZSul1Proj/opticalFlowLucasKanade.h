#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>

int computeOpticalFlow(cv::Mat *gray, cv::Mat *prevGray, std::vector<cv::Point2f> *points, std::vector<cv::Point2f> *prevPoints);
int showOpticalFlow();