#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void seeTheChannels() {
	Mat img = imread("Resources/kurama.jpg");
	vector<Mat> channels;
	split(img, channels);
	imshow("blue", channels[0]);
	imshow("green", channels[1]);
	imshow("red", channels[2]);
	waitKey();
}

void copyNonWhite() {
	Mat kurama = imread("Resources/kurama.jpg");
	Mat background = imread("Resources/background.jpg");
	resize(background, background, kurama.size());
	for (int y = 0; y < kurama.rows; y++) {
		for (int x = 0; x < kurama.cols; x++) {
			if (kurama.at<Vec3b>(y, x) != Vec3b(255, 255, 255)) {
				background.at<Vec3b>(y, x) = kurama.at<Vec3b>(y, x);
			}
		}
	}
	imshow("Result", background);
	waitKey(0);
	destroyAllWindows();
}

void copyOrange() {
	Mat orange = imread("Resources/orange1.jpg", IMREAD_COLOR);
	Mat black = Mat::zeros(orange.size(), CV_8UC3);
	assert(!orange.empty());
	for (int y = 0; y < orange.rows; y++) {
		for (int x = y; x < orange.cols; x++) {
			Vec3b color = orange.at<Vec3b>(y, x);
			if (color[2] > 140 && color[1] < 190 && color[0] < 80) {
				black.at<Vec3b>(y, x) = color;
			}
		}
	}
	imshow("Orange", orange);
	imshow("Black", black);
	waitKey(0);
}

void copyOrangeWithRange() {
	Mat orange = imread("Resources/orange1.jpg", IMREAD_COLOR);
	assert(!orange.empty());
	Mat dest = Mat::zeros(orange.size(), orange.type());
	Scalar lb(0, 100, 200);
	Scalar ub(50, 200, 255);
	Mat mask;
	inRange(orange, lb, ub, mask);
	orange.copyTo(dest, mask);
	imshow("Oranges", dest);
	waitKey(0);

}

void copyOrangeHSV() {
	Mat src = imread("Resources/orange1.jpg", IMREAD_COLOR);
	assert(!src.empty());
	Mat dest = Mat::zeros(src.size(), src.type());
	Mat hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);
	Scalar lower(0, 50, 50);
	Scalar upper(30, 255, 255);
	Mat mask;
	inRange(hsv, lower, upper, mask);
	src.copyTo(dest, mask);
	imshow("Orange in HSV", dest);
	waitKey(0);
}
void convert_labf(const Mat rgb, Mat& dest) {
	// Converting the type from integer to float.
	// We also change the range [0, 255] --> [0, 1]
	Mat rgbf;
	rgb.convertTo(rgbf, CV_32FC3, 1 / 255.0);
	// We change the color space (result image: CV_32FC)3
	cvtColor(rgbf, dest, COLOR_BGR2Lab);
}
string category(double diff) {
	if (diff <= 1.0)
		return "Not perceptible";
	if (diff <= 2.0)
		return "Perceptible (close obs.)";
	if (diff <= 10.0)
		return "Perceptible at a glance";
	return "Big differences"; // for the last two categories. diff >10
}

void totalDifferenceBetweenTwoPixels(string path) {
	Mat img = imread(path);
	Mat img_lab;
	convert_labf(img, img_lab);
	// imwrite("lab.png", img_lab);
	// accessing the pixel at the upper-left corner
	Vec3f p1 = img_lab.at<Vec3f>(0, 0);
	// accessing the pixel at the bottom-right corner
	Vec3f p2 = img_lab.at<Vec3f>(img.rows - 1, img.cols - 1);
	double diff = cv::norm(p1 - p2);
	std::cout << category(diff) << endl;
}
double compareImg(const Mat etalon_lab, const Mat img_lab) {
	Mat diff = etalon_lab - img_lab;

	// pixel-wise multiplication (power 2)
	Mat diff2 = diff.mul(diff);

	// split the channels
	vector<Mat> chs;
	split(diff2, chs);

	// Use the + matrix operator
	Mat dist;
	cv::sqrt(chs[0] + chs[1] + chs[2], dist);

	// mean of the difference
	return mean(dist)[0];
}
int main() {
	return 0;
}