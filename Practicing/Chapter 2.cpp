#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	string path = "Resources/test.png";
	Mat img = imread(path), imgGrey, imgBlur,imgCanny, imgDil, imgErode;
	cvtColor(img, imgGrey, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur,Size(3,3),3,0);
	Canny(imgBlur, imgCanny, 50, 150);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);
	imshow("Image", img);
	imshow("Image Grey", imgGrey);
	imshow("Image Blurr", imgBlur);
	imshow("Image Canny", imgCanny);
	imshow("Image Dil", imgDil);
	imshow("Image Erode", imgErode);
	waitKey();
	return 0;
}