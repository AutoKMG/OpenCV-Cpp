#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("Resources/go2.png", IMREAD_GRAYSCALE);
	imshow("img", img);
	vector<Vec3f> circles;
	HoughCircles(img, circles, HOUGH_GRADIENT, 2, 10.0, 80, 40, 22, 24);
	Mat canvas;
	cvtColor(img, canvas, COLOR_GRAY2BGR);
	Scalar for_black_stone(255, 0, 0);
	Scalar for_white_stone(0, 0, 255);
	for (Vec3f c : circles) {
		if(img.at<uchar>(Point(c[0],c[1])) > 128) {
			circle(canvas, Point(c[0], c[1]), c[2], for_white_stone, 2);
		}
		else {
			circle(canvas, Point(c[0], c[1]), c[2], for_black_stone, 2);
		}
	}
	imshow("circles", canvas);
	waitKey();
	return 0;
}