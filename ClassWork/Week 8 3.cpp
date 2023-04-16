#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("Resources/cheese.png", IMREAD_GRAYSCALE);
	Mat mask;
	threshold(img, mask, 250, 255, THRESH_BINARY_INV);
	medianBlur(mask, mask, 5);
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_EXTERNAL,CHAIN_APPROX_NONE);
	cout << contours.size();
	Mat canvas;
	cvtColor(img, canvas, COLOR_GRAY2BGR);
	drawContours(canvas, contours, -1, Scalar(0, 255, 0), 2);
	imshow("mask", mask);
	imshow("canvas", canvas);
	imshow("img", img);
	imshow("mask", mask);
	waitKey();
	return 0;
}