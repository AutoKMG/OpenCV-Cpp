#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("Resources/gray_buttons.jpg", IMREAD_GRAYSCALE);
	Mat mask;

	inRange(img, 165, 213, mask);
	medianBlur(mask, mask, 5);
	Mat dest;
	img.copyTo(dest, mask);
	imshow("img", img);
	imshow("mask", mask);
	imshow("result", dest);
	waitKey();
	return 0;
}