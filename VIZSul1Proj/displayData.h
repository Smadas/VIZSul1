#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void displayVectorY(cv::Mat *img, double direction, cv::Point centerPoint);
void displayVectorXZ(cv::Mat *img, float x, float y, double angle, cv::Point centerPoint);