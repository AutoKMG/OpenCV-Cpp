#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat_<Vec3b> m(2, 3, CV_8UC3);
	m(0, 0) = Vec3b(0, 0, 255);
	m(0, 1) = Vec3b(0, 255, 0);
	m(0, 2) = Vec3b(255, 0, 0);
	m(1, 0) = Vec3b(0, 0, 0);
	m(1, 1) = Vec3b(39, 127, 255);
	m(1, 2) = Vec3b(0, 255, 255);
	namedWindow("sample", WINDOW_NORMAL);
	resizeWindow("sample", 120, 80);
	imshow("sample", m);
	waitKey(0);
	return 0;
}