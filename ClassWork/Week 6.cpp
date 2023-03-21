#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("Resources/dog.jpg", IMREAD_GRAYSCALE);
	Mat filtered;
	GaussianBlur(img, filtered, Size(5, 5), 1.5);
	Mat mask;
	threshold(img, mask, 138, 255, THRESH_TOZERO);
	medianBlur(mask, mask, 5);
	imshow("img", img);
	imshow("filtered", filtered);
	imshow("mask", mask);
	waitKey();
	return 0;
}