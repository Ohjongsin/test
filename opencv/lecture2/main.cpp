#include "main.h"

void main() {

	/*Mat input = imread("overlay_text.bmp", 0);
	Mat input_COLOR = imread("overlay_text.bmp", 1);

	int height = input.rows;
	int width = input.cols;
	float R[1440*860];
	corner_detector(input, R);
	BoxGernerationandinpaint(input_COLOR, input, R);*/

	Mat input = imread("image.jpg", 1);
	Mat sk;
	Mat hsv;
	Mat eye;
	int flag = 0;
	int height = input.rows;
	int width = input.cols;
	int x, y;


	cvtColor(input, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 48, 80), Scalar(20, 255, 255), hsv);
	imwrite("./test/hsvtest.bmp", hsv);
	sk = (hsv.size(), CV_8UC3, Scalar(0));
	//imwrite("./test/sskk.bmp", sk);
	add(input, Scalar(0), sk, hsv);
	imwrite("./test/hsvskin.bmp", sk);
}