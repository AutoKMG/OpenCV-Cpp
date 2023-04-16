#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {
	Mat img;

	for (int i = 0; i <= 20; ++i) {
		img = imread("Resources/hela/" + to_string(i) + ".png", IMREAD_GRAYSCALE);
		vector<Vec3f> circles;
		HoughCircles(img, circles, HOUGH_GRADIENT_ALT, 2, 10.0, 80, 0.7, 18, 33);
		Mat canvas;
		cvtColor(img, canvas, COLOR_GRAY2BGR);

		Scalar round_cells(0, 0, 255);
		for (Vec3f c : circles) {
			circle(canvas, Point(c[0], c[1]), c[2], round_cells, 2);
		}
		imshow("canvas", canvas);
		waitKey(0);
	}
	waitKey();
	return 0;
}