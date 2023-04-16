#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void readDisplayWaitforImage() {
	Mat img = imread("Resources/dog.jpg");
	imshow("my window", img);
	waitKey();
}
void eightBitGrayscale20050() {
	Mat image(200, 50, CV_8UC1);
	imshow("Grayscale Image", image);
	waitKey(0);
}
void twentyfourColorImage50200() {
	Mat image(50, 200, CV_8UC3);
	imshow("Color Image", image);
	waitKey(0);
}
void black8bitGrayscaleImage2040() {
	Mat image = Mat::zeros(20, 40, CV_8UC1);
	imshow("Black Grayscale Image", image);
	waitKey(0);
}
void white8bitGrayscale2040() {
	Mat image = Mat(20, 40, CV_8UC1, Scalar(255));
	image.setTo(Scalar(255));
	imshow("White Grayscale Image", image);
	waitKey(0);
}
void red24bitColorImage99121() {
	Mat image(99, 121, CV_8UC3, Scalar(0, 0, 255));
	image.setTo(Scalar(0, 0, 255));
	imshow("Red Color Image", image);
	waitKey(0);
}
void readImageCreateSameType() {
	Mat inputImage = imread("Resources/dog.jpg");
	Mat outputImage(inputImage.size(), inputImage.type());
	imshow("Input Image", inputImage);
	imshow("Output Image", outputImage);
	waitKey(0);
}
void readImageCreateHalfWidth() {
	Mat inputImage = imread("Resources/dog.jpg");
	Mat outputImage(inputImage.rows / 2, inputImage.cols, inputImage.type());
	imshow("Input Image", inputImage);
	imshow("Output Image", outputImage);
	waitKey(0);
}

void shallowCopy() {
	Mat A(2, 3, CV_8U), B;
	B = A;
	imshow("A", A);
	imshow("B", B);
	waitKey(0);
}
void deepCopy() {
	Mat A(2, 3, CV_8U), B, C;
	B = A.clone();
	A.copyTo(C);
	imshow("A", A);
	imshow("B", B);
	imshow("C", C);
	waitKey();
}

void loadKuramaImageShallowCopy() {
	Mat inputImage = imread("Resources/kurama.jpg");
	Mat outputImage = inputImage;
	outputImage.setTo(Scalar(0, 0, 255));
	imshow("Input Image", inputImage);
	imshow("Output Image", outputImage);
	waitKey();
}
void loadKuramaImageDeepCopy() {
	Mat inputImage = imread("Resources/kurama.jpg");
	Mat outputImage = inputImage.clone();
	outputImage.setTo(Scalar(0, 0, 255));
	imshow("Input Image", inputImage);
	imshow("Output Image", outputImage);
	waitKey();
}

void imageWholeRedUpperPartYellow400600() {
	Mat img(400, 600, CV_8UC3);
	img.setTo(Scalar(0, 0, 255));
	Rect roi(0, 0, 600, 200);
	Mat upperHalf = img(roi);
	upperHalf.setTo(Scalar(0, 255, 255));
	imshow("Image", img);
	waitKey();

}

void cropKuramaImage() {
	Mat img = imread("Resources/kurama.jpg");
	Rect roi(20, 20, img.cols - 40, img.rows - 40);
	Mat cropped = img(roi);
	imwrite("my_image.png", cropped);
	imshow("cropped", cropped);
	imshow("original", img);
	waitKey();
}
void kuramaImageResizedandOnBackground() {
	Mat kurama = imread("Resources/kurama.jpg");
	resize(kurama, kurama, Size(400, 400));
	Mat background = imread("Resources/background.jpg");
	int x = (background.cols - 400) / 2;
	int y = (background.rows - 400) / 2;
	Rect roi(x, y, 400, 400);
	Mat destination = background(roi);
	kurama.copyTo(destination);
	imshow("Result", background);
	waitKey();
}
void grayscaleImageFadedDarker() {
	Mat img = imread("Resources/gray_buttons.jpg", IMREAD_GRAYSCALE);
	int add_value = 100;
	Mat faded_img = img + add_value;
	int subtract_value = 100;
	Mat darker_img = img - subtract_value;
	imshow("Original Image", img);
	imshow("Faded Image", faded_img);
	imshow("Darker Image", darker_img);
	waitKey(0);
	destroyAllWindows();
}
void invertingAnImage() {
	Mat img = imread("Resources/gray_buttons.jpg", IMREAD_GRAYSCALE);
	Mat inverted_img = 255 - img;
	Mat subtracted_img;
	subtract(Scalar(255), img, subtracted_img);

	imshow("Inverted Image", inverted_img);
	imshow("Subtracted Image", subtracted_img);
	waitKey(0);
	destroyAllWindows();
}

void blendingTwoImages() {
	Mat background = imread("Resources/background.jpg");
	Mat cartoon = imread("Resources/kurama.jpg");
	resize(background, background, cartoon.size());
	double alpha = 0.25;
	Mat blended = alpha * cartoon + (1 - alpha) * background;
	namedWindow("Background", WINDOW_NORMAL);
	namedWindow("Cartoon", WINDOW_NORMAL);
	namedWindow("Blended", WINDOW_NORMAL);
	imshow("Background", background);
	imshow("Cartoon", cartoon);
	imshow("Blended",blended);
	waitKey(0);
}

void createSixSquaresColoredImage() {
	Mat m(2, 3, CV_8UC3);
	m.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);
	m.at<Vec3b>(0, 1) = Vec3b(0, 255, 0);
	m.at<Vec3b>(0, 2) = Vec3b(255, 0, 0);
	m.at<Vec3b>(1, 0) = Vec3b(0, 0, 0);
	m.at<Vec3b>(1, 1) = Vec3b(39, 127, 255);
	m.at<Vec3b>(1, 2) = Vec3b(0, 255, 255);
	namedWindow("sample", WINDOW_NORMAL);
	resizeWindow("sample", 120, 80);
	imshow("sample", m);
	waitKey(0);
	destroyAllWindows();
}
int main() {
	createSixSquaresColoredImage();
	return 0;
}