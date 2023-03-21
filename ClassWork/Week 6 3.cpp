#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(){
	VideoCapture cap;
	cap.open("Resources/sas.avi");
	if (!cap.isOpened()) {
		cout << "do you have the file?" << endl;
		exit(-1);
	}
	Mat img, gray, mask;
	while (1) {
		cap >> img;
		if (img.empty())
			break;
		cvtColor(img, gray, COLOR_BGR2GRAY);
		inRange(gray, 100, 155, mask);
		medianBlur(mask, mask, 9);
		img.setTo(Scalar(0, 0, 0), mask);
		imshow("frame", img);
		imshow("sky mask", mask);
		imshow("gray", gray);
		waitKey(25);
	}
	return 0;
}