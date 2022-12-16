//#include "main.h"
//
//void main() {
//
//	int x, y;
//
//	Mat test = imread("input.jpg", 1);
//	Mat mask = imread("Mask_test.bmp",1);
//
//	int height = mask.rows;
//	int width = mask.cols;
//	
//	Mat maskN(height, width, CV_8UC1);
//	Mat result(height, width, CV_8UC3);
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if (mask.at<Vec3b>(y, x)[0] == 255 && mask.at<Vec3b>(y, x)[1] == 255 && mask.at<Vec3b>(y, x)[2] == 255)
//				maskN.at<uchar>(y, x) = 255;
//			else
//				maskN.at<uchar>(y, x) = 0;
//		}
//	}
//	inpaint(test, maskN, result, 3, INPAINT_TELEA);
//	
//	imwrite("RESULT.bmp", result);
//
//}