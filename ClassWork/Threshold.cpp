#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;


void thresholdFirst() {
    // Load image in grayscale
    Mat img = imread("Resources/dog.jpg", IMREAD_GRAYSCALE);

    // Threshold with THRESH_BINARY method
    Mat thresh1;
    threshold(img, thresh1, 100, 255, THRESH_BINARY);

    // Threshold with THRESH_OTSU method
    Mat thresh2;
    double th = threshold(img, thresh2, 0, 255, THRESH_OTSU);
    cout << "Computed threshold value: " << th << endl;

    // Display images
    imshow("Original", img);
    imshow("THRESH_BINARY", thresh1);
    imshow("THRESH_OTSU", thresh2);
    waitKey(0);
}

void readGrayButtons() {
    Mat img = imread("Resources/gray_buttons.jpg");
    Mat mask;
    threshold(img, mask, 213, 255, THRESH_BINARY);
    threshold(img, mask, 165, 255, THRESH_BINARY);
    medianBlur(mask, mask, 5);
    bitwise_not(mask, mask);
    img.setTo(Scalar(0), mask);
    imshow("result", img);
    waitKey(0);
    destroyAllWindows();
}

void showBlackBear() {
    // Load the image in color
    Mat img = imread("Resources/black_bear.jpg", IMREAD_COLOR);

    // Convert it to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Threshold the grayscale image to create a mask
    Mat mask;
    threshold(gray, mask, 140, 255, THRESH_BINARY);
    // bitwise_not(mask, mask);

    // Apply a median filter to remove some noise
    medianBlur(mask, mask, 11);

    // Apply the Watershed algorithm to the mask

    // Create a new green image with the size and the type of the original image
    Mat result(img.size(), img.type(), Scalar(0, 255, 0));
    img.copyTo(result, mask);

    // Show the original and the result images
    imshow("Original Image", img);
    imshow("Result Image", result);
    waitKey(0);
}

void thresholdEskimoDog() {
    // Load the image in color
    Mat img = imread("Resources/dog.jpg", IMREAD_COLOR);

    // Convert to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Threshold the grayscale image
    Mat mask;
    threshold(gray, mask, 100, 255, THRESH_BINARY);

    // Copy the dog from the original image to a new one
    Mat dog;
    img.copyTo(dog, mask);

    // Show the original and result images
    imshow("Original Image", img);
    imshow("Dog Image", dog);
    waitKey(0);

    // Alternatively, to remove the background of the original image
    Mat mask_inv;
    threshold(gray, mask_inv, 100, 255, THRESH_BINARY_INV);
    img.setTo(Scalar(0, 0, 0), mask_inv);

    // Show the result image
    imshow("Removed Background Image", img);
    waitKey(0);
}

void birdImageSpltiChannel() {
    Mat img = imread("Resources/blue_bird.jpg", IMREAD_COLOR);
    vector<Mat> channels;
    split(img, channels);
    Mat mask = channels[0] > 100;
    Mat result;
    img.copyTo(result, mask);

    imshow("Original Image", img);
    imshow("Mask", mask);
    imshow("Result", result);
    waitKey(0);
}

void openingVideo() {
    VideoCapture cap("Resources/sas.avi");

    // Check if the video has been opened
    if (!cap.isOpened()) {
        std::cout << "Error opening video file!\n";
    }

    // Process each frame of the video
    Mat frame, gray, mask;
    while (cap.read(frame)) {
        // Clone the image to make modifications
        Mat img = frame.clone();

        // Convert to grayscale
        cvtColor(img, gray, COLOR_BGR2GRAY);

        // Threshold the grayscale image to get the mask of the sky
        inRange(gray, Scalar(100), Scalar(155), mask);

        // Smooth the mask with median blur
        medianBlur(mask, mask, 5);

        // Remove the sky pixels from the image
        img.setTo(0, mask);

        // Display the original image and the result
        imshow("Original", frame);
        imshow("Result", img);

        // Wait for 0.1 seconds
        if (waitKey(100) == 27) {
            break; // ESC key is pressed
        }
    }

    // Release the video capture object and close all windows
    cap.release();
    destroyAllWindows();
}

void flower2Image() {
    Mat img = imread("Resources/flower2.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "Could not read the image!" << endl;
    }

    // Apply a 5x5 Gaussian filter with sigma=1.5
    Mat img_blur;
    GaussianBlur(img, img_blur, Size(5, 5), 1.5);

    // Apply a global threshold to get the mask of the foreground
    Mat mask;
    threshold(img_blur, mask, 140, 255, THRESH_BINARY);

    // Apply a 9x9 median filter on the mask
    medianBlur(mask, mask, 9);

    // Show the original and the result images
    namedWindow("Original Image", WINDOW_NORMAL);
    namedWindow("Result Image", WINDOW_NORMAL);

    imshow("Original Image", img);
    imshow("Result Image", mask);

    waitKey(0);
    destroyAllWindows();
}

void flower2ImageRemoveBackground(){
    Mat img = imread("Resources/flower2.jpg", IMREAD_COLOR);
    Mat img_grayscale;
    cvtColor(img, img_grayscale, COLOR_BGR2GRAY);
    GaussianBlur(img_grayscale, img_grayscale, Size(9,9), 1.5);
    Mat mask;
    threshold(img, mask, 150, 255, THRESH_BINARY);
    medianBlur(mask, mask, 9);
    Mat result = Mat::zeros(img.size(),CV_8UC3);
    img.copyTo(result, mask);
    imshow("result", result);
    waitKey();
}
void flower2ImageRemoveBackground2() {
    Mat img = imread("Resources/flower2.jpg");

    // Convert to grayscale
    Mat gray_img;
    cvtColor(img, gray_img, COLOR_BGR2GRAY);

    // Apply Gaussian filter with 5x5 kernel and sigma=1.5
    Mat blurred_img;
    GaussianBlur(gray_img, blurred_img, Size(5, 5), 1.5);

    // Apply global threshold to get foreground
    Mat mask;
    threshold(blurred_img, mask, 160, 255, THRESH_BINARY);

    // Apply median filter with 9x9 kernel
    medianBlur(mask, mask, 9);

    // Create new black image
    Mat result(img.size(), CV_8UC3, Scalar(0, 0, 0));

    // Copy flower to new image using mask
    img.copyTo(result, mask);

    // Display images
    namedWindow("Original Image", WINDOW_NORMAL);
    imshow("Original Image", img);

    namedWindow("Result Image", WINDOW_NORMAL);
    imshow("Result Image", result);

    waitKey(0);
    destroyAllWindows();
}
void catImage() {
    Mat img = imread("Resources/red_cat.png", IMREAD_COLOR);
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    vector<Mat> channels;
    split(imgHSV, channels);
    Mat mask;
    threshold(channels[1], mask, 40, 255, THRESH_BINARY);
    medianBlur(mask, mask, 9);
    Mat result = Mat::zeros(img.size(), CV_8UC3);
    img.copyTo(result, mask);
    imshow("original", img);
    imshow("result", result);
    waitKey(0);
}
int main() {
    showBlackBear();
    return 0;
}