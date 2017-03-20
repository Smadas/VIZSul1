#include "opticalFlowLucasKanade.h"
#include "DetectTarget.h"

int main()
{
	//if (0 != showOpticalFlow()) {
	//}
	//return 0;

	// Get circle center and radius [x,y,radius]
	Vec3f circle;
	Mat src = imread("TestImage.bmp", IMREAD_COLOR);
	circle = findCircle(src);
	

}