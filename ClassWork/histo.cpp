/*
Kepfeld. gyak. - nehany segedfuggveny az orai anyag konnyebb szemleltetesehez.
*/

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "histo.h"

using namespace std;
using namespace cv;

void Histo::calcHistoC1(const cv::Mat img, cv::Mat& histo) {
	assert(img.type() == CV_8UC1);

	// CV_32U nem letezik, ha de CV_16U-t (ushort) hasznalhatsz, ha akarsz.
	histo = Mat::zeros(256, 1, CV_32S);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			histo.at<int>(img.at<uchar>(i, j))++;
}


void Histo::calcHistoC3(const cv::Mat img, vector<cv::Mat>& histo_vect) {
	assert(img.type() == CV_8UC3);

	vector<Mat> chs;
	split(img.clone(), chs);

	Mat h0, h1, h2;
	Histo::calcHistoC1(chs[0], h0);
	Histo::calcHistoC1(chs[1], h1);
	Histo::calcHistoC1(chs[2], h2);

	histo_vect.clear();
	histo_vect.push_back(h0);
	histo_vect.push_back(h1);
	histo_vect.push_back(h2);
}



void Histo::drawHistoC1(const cv::Mat histo, cv::Mat& canvas, int channel) {
	assert(histo.type() == CV_32S);

	int pad = 10;
	canvas = Mat::zeros(200 + 2 * pad, 256 + 2 * pad, CV_8UC3);
	
	// a hisztogram alatti szurke sav rajzolasa 
	for (int i = 0; i < 10; ++i) {  // 10 pixel vastag lesz, hogy jol latszodjon
		for (int j = 0; j < 256; ++j) {
			if (0 <= channel && channel <= 2) {
				canvas.at<Vec3b>(canvas.rows - 1 - i, j + pad)[channel] = j;
			}
			else {
				canvas.at<Vec3b>(canvas.rows - 1 - i, j + pad) = Vec3b(j, j, j);
			}
		}
	}
	

	Vec3b color(255, 255, 255);
	if (0 <= channel && channel <= 2) {
		color = Vec3b(0, 0, 0);
		color[channel] = 255;
	}


	double minv, maxv;
	minMaxLoc(histo, &minv, &maxv);
	
	double scale = 200 / maxv;  // az ablak magassagahoz igazitom a hisztogram magassagat

	// a hisztogram rajzolasa
	for (int i = 0; i < 256; ++i) {
		// egy oszlop magassage (a line(Point(0, 0), Point(0, 1)) 2 pixelt rajzolna, ezert a -1)
		int v = int(histo.at<int>(i) * scale) - 1; 
		// canvas.rows-2-pad oldja meg, hogy a szurke sav felett kezdjuk a rajzolast
		if (v >= 0)
			line(canvas, Point(pad + i, canvas.rows - 2 - v - pad), Point(pad + i, canvas.rows - 2 - pad), color);
	}
}


void Histo::drawHistoC3(const vector<cv::Mat> histos, vector<cv::Mat>& canvases) {
	assert(histos.size() == 3 && 
		   histos[0].type() == CV_32S && histos[1].type() == CV_32S && histos[2].type() == CV_32S);

	canvases.clear();
	for (int i = 0; i <= 2; ++i) {
		Mat canvas;
		Histo::drawHistoC1(histos[i], canvas, i);
		canvases.push_back(canvas.clone());
	}
}


void Histo::showHisto(Mat img, string title, int wait) {
	assert(img.type() == CV_8UC1 || img.type() == CV_8UC3);

	if (img.type() == CV_8UC1) {
		Mat histo;
		Histo::calcHistoC1(img, histo);

		// az ertekek konzolra iratasa
		//cout << histo << endl;

		Mat canvas;
		Histo::drawHistoC1(histo, canvas);
		imshow(title, canvas);
	}
	else if (img.type() == CV_8UC3) {
		vector<Mat> histos;
		Histo::calcHistoC3(img, histos);

		vector<Mat> canvases;
		Histo::drawHistoC3(histos, canvases);

		string str = "BGR";
		for (int i = 0; i <= 2; ++i) {
			imshow(title + "-" + str[i], canvases[i]);
		}
	}
	waitKey(wait);
}
