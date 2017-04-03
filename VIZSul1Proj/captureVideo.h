#pragma once

#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\objdetect\objdetect.hpp"
#include "opencv2/video/tracking.hpp"

void saveFrame(cv::Mat src);
void captureVideoAsImages(int cameraID);
