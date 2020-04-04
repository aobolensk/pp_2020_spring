// #include "../../../modules/task_3/mityagina_d_increasing_the_contrast/increasing_the_contrast.h"
// #include <opencv2/opencv.hpp>
// #include <iostream>
// #include <cmath>
// #include <string>

// using namespace cv;
// using namespace std;

// void histStretch(Mat &src, Mat &dst); //Histogram equalization
// void drawHist(const Mat &src, Mat &dst); // Draw Histogram

// int main()
// {
// 	Mat image, hist1, hist2;
// 	int histSize = 256;
// 	float range[] = { 0, 255 };
// 	const float* histRange = { range };

// 	string file;
// 	cout << "Enter the file name: ";
// 	cin >> file;
		
// 	image = imread(file, CV_LOAD_IMAGE_GRAYSCALE);

// 	if (!image.data) {
// 		cout << "Could not open or find the image" << endl;
// 		system("pause");
// 		return -1;
// 	}
// 	Mat out = Mat::zeros(image.size(), image.type());

// 	histStretch(image, out); //eq

// 	namedWindow("Original", CV_WINDOW_AUTOSIZE);
// 	imshow("Original", image);
// 	waitKey(0);

// 	calcHist(&image, 1, 0, Mat(), hist1, 1, &histSize, &histRange);
// 	Mat showHist1(256, 256, CV_8UC1, Scalar(255));
// 	drawHist(hist1, showHist1);

// 	namedWindow("Histogram(Original)", CV_WINDOW_AUTOSIZE);
// 	imshow("Histogram(Original)", showHist1);
// 	waitKey(0);

// 	namedWindow("Histogram stretch", CV_WINDOW_AUTOSIZE);
// 	imshow("Histogram stretch", out);
// 	waitKey(0);

// 	calcHist(&out, 1, 0, Mat(), hist2, 1, &histSize, &histRange);
// 	Mat showHist2(256, 256, CV_8UC1, Scalar(255));
// 	drawHist(hist2, showHist2);

// 	namedWindow("Histogram(changed)", CV_WINDOW_AUTOSIZE);
// 	imshow("Histogram(changed)", showHist2);
// 	waitKey(0);

// 	imwrite("Histogram_stretched.jpg", out);

// 	return 0;
// }

// void histStretch(Mat &src, Mat &dst)
// {
// 	int gray[256] {0};
// 	for (int y = 0; y < src.rows; y++) { 
// 		for (int x = 0; x < src.cols; x++) {
// 			gray[(int)src.at<uchar>(y, x)]++;
// 		} 
// 	}
// 	std::vector<int> fake = std::vector<int>(src.rows * src.cols);
// 	for (int y = 0; y < src.rows; y++) {
// 		for (int x = 0; x < src.cols; x++) {
// 			fake[y * src.cols + x] = (int)src.at<uchar>(y, x);
// 		}
// 	}

// 	std::vector<int> out = contrast_increase_sequential(fake, src.cols, src.rows);

// 	for (int y = 0; y < src.rows; y++) {
// 		for (int x = 0; x < src.cols; x++) {
// 			dst.at<uchar>(y, x) = (uchar)out[y * src.cols + x];
// 		}
// 	}
// }

// void drawHist(const Mat &src, Mat &dst)
// {
// 	int histSize = 256;
// 	float histMax = 0;
// 	for (int i = 0; i < histSize; i++) {
// 		float temp = src.at<float>(i);
// 		if (histMax < temp) {
// 			histMax = temp;
// 		}
// 	}

// 	float scale = (0.9 * 256) / histMax;
// 	for (int i = 0; i < histSize; i++) {
// 		int intensity = static_cast<int>(src.at<float>(i)*scale);
// 		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
// 	}
// }