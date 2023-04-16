#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void histogram() {
    Mat img = imread("Resources/dog.jpg", IMREAD_GRAYSCALE);
    Mat histo;
    histo = Mat::zeros(256, 1, CV_32S);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int v = img.at<uchar>(i, j);
            histo.at<int>(v, 0)++;
        }
    }
    cout << histo << endl;
    waitKey();
}

void imageEnhanceFirst() {
    Mat img = imread("Resources/dark_img.jpg",IMREAD_GRAYSCALE);
    double min, max;
    minMaxLoc(img, &min, &max);
    Mat dest = (img - min) * (255 / (max - min));
    imshow("img", img);
    imshow("dest", dest);
    waitKey();
}

void medianBoxGaussianFilters() {
    Mat orange = imread("Resources/orange.jpg", IMREAD_COLOR);
    Mat median_filtered;
    medianBlur(orange, median_filtered, 5);

    Mat box_filtered;
    boxFilter(orange, box_filtered, -1, Size(15, 15));

    Mat gaussian_filtered;
    GaussianBlur(orange, gaussian_filtered, Size(11, 11), 2.0);
    imshow("original", orange);
    imshow("Median filtered", median_filtered);
    imshow("Box filtered", box_filtered);
    imshow("Gaussian filtered", gaussian_filtered);
    waitKey(0);
}

void helaFolder() {
    for (int i = 0; i <= 20; i++) {
        // Read the image in grayscale
        Mat img = imread("Resources/hela/" + to_string(i) + ".png", IMREAD_GRAYSCALE);
        if (img.empty()) {
            cerr << "Could not read image: " << i << endl;
            continue;
        }

        // Apply a large median filter
        Mat bg;
        medianBlur(img, bg, 51);

        // Show the result
        imshow("Background", bg);
        waitKey();

        // Remove the background using the minus operator
        Mat result1 = img - bg;

        // Show the result
        imshow("Result 1", result1);
        waitKey();

        // Remove the background using absdiff
        Mat result2;
        absdiff(img, bg, result2);

        // Show the result
        imshow("Result 2", result2);
        waitKey();
    }
}

int main() {
    helaFolder();
    return 0;
}