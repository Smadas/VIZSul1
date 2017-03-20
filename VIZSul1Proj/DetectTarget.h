#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <stdlib.h>

using namespace cv;

Vec3f findCircle(Mat src);
std::vector<Vec2i> findPoints(Mat src);