#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("Resources/kinect_depth.png", IMREAD_GRAYSCALE);
	Mat mask;
	threshold(img, mask, 140, 255, THRESH_BINARY);
	medianBlur(mask, mask, 7);
	imshow("frame", mask);
	waitKey();
	return 0;
}