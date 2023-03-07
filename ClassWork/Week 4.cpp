#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "histo.h"

using namespace std;
using namespace cv;

string category(double diff) {
	if (diff <= 1.0)
		return "Not perceptible";
	if (diff <= 2.0)
		return "Perceptible (close obs.)";
	if (diff <= 10.0)
		return "Perceptible at a glance";
	return "Big differences"; // for the last two categories. diff >10
}

void convert_labf(const Mat rgb, Mat& dest) {
	// Converting the type from integer to float.
	// We also change the range [0, 255] --> [0, 1]
	Mat rgbf;
	rgb.convertTo(rgbf, CV_32FC3, 1 / 255.0);
	// We change the color space (result image: CV_32FC)3
	cvtColor(rgbf, dest, COLOR_BGR2Lab);
}

double compareImg(const Mat etalon_lab, const Mat img_lab) {
	// Use the matrix operator to compute the :
	Mat diff = etalon_lab - img_lab;
	// pixel-wise multiplication (power 2)
	Mat diff2 = diff.mul(diff);  // 1 image with 3 channel
	// split the channels
	vector<Mat> chs;
	split(diff2, chs);  // 3 images with 1 channel
	// Use the + matrix operator
	Mat dist;
	cv::sqrt(chs[0] + chs[1] + chs[2], dist);
	// mean of the difference
	return mean(dist)[0];
}

void histogram(const Mat img, Mat& histo) {
		histo = Mat::zeros(256, 1, CV_32S);
		for (int i =0; i<img.rows; ++i)
			for (int j = 0; j < img.cols;++j) {
				int v = img.at<uchar>(i, j);
				histo.at<int>(v)++;
			}
}
int main() {
	Mat img = imread("Resources/orange1.jpg");
	vector<Mat> chs;
	split(img, chs);
	equalizeHist(chs[0], chs[0]);
	equalizeHist(chs[1], chs[1]);
	equalizeHist(chs[2], chs[2]);
	Mat dest;
	merge(chs, dest);

	imshow("img", img);
	Histo::showHisto(img);
	imshow("img2", dest);
	Histo::showHisto(dest);
	waitKey(0);

	return 0;
}