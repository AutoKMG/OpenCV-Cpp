#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
	
	Mat bridge = imread("bridge.jpg");
	Mat flower = imread("flower.jpg");
	resize(bridge, bridge, flower.size());
	double a = 0.5;
	Mat newImg = a * flower + (1 - a) * bridge ;
	imshow("result", newImg);
	/*Mat dest = background + 100;
	Mat dest2 = background - 100;
	Mat inverted = 255 - background;
	imshow("original", background);
	imshow("fadded", dest);
	imshow("darker", dest2);
	imshow("inverted", inverted);*/
	waitKey();
	return 0;
}