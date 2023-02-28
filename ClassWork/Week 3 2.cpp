#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void convert_labf(const Mat rgb, Mat& dest) {
	// Converting the type from integer to float.
	// We also change the range [0, 255] --> [0, 1]
	Mat rgbf;
	rgb.convertTo(rgbf, CV_32FC3, 1 / 255.0);
	// We change the color space (result image: CV_32FC)3
	cvtColor(rgbf, dest, COLOR_BGR2Lab);
}

void copyKurama(const Mat img, Mat& background) {
	resize(background, background, img.size());

	Vec3b c;

	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			c = img.at<Vec3b>(i, j);
			if (c[0] < 100 || c[1] < 100 || c[2] < 100) {
				// cout << "The condition is working";
				background.at<Vec3b>(i, j) = c;
			}
		}
	}
}

void copyOrangeHSV(const Mat img, Mat& background) {
	background = Mat::zeros(img.size(), img.type());
	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV);
	Vec3b c, c2;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			c = img.at<Vec3b>(i, j);
			c2 = hsv.at<Vec3b>(i, j);
			if (c2[0] < 30) {
				background.at<Vec3b>(i, j) = c;
			}
		}
	}
}
void copyGreenHSV(const Mat img, Mat& background) {
	background = Mat::zeros(img.size(), img.type());
	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV);
	Vec3b c, c2;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			c = img.at<Vec3b>(i, j);
			c2 = hsv.at<Vec3b>(i, j);
			if (60 < c2[0] && c2[0] < 120) {
				background.at<Vec3b>(i, j) = c;
			}
		}
	}
}

int main() {
	Mat img = imread("Resources/green_red_stain.jpg");
	Mat lab;
	convert_labf(img, lab);
	cout << norm(lab.at<Vec3f>(0, 0) - lab.at<Vec3f>(0,1));
	Mat dest;
	copyGreenHSV(img, dest);
	// copyKurama(img, background);
	imshow("dest", dest);
	waitKey();
	return 0;
}