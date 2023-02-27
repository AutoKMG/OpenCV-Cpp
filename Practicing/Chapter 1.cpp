#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream> 

using namespace cv;
using namespace std;

void image() {
	// we read an image
	Mat img = imread("Resources/test.png");
	// and display it in a window
	imshow("my window", img);
	// we wait for key press
	waitKey();
}

void video() {
	string path = "Resources/test_video.mp4";
	VideoCapture cap(path);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("My Video", img);
		waitKey(15);
	}
}

void webcam() {
	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("My Video", img);
		waitKey(1);
	}
}

int main() {
	// image();
	// video();
	webcam();
	return 0;
}
