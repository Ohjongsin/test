#include "main.h"

void main() {

	Mat hair = imread("./last/hair.bmp",1);
	Mat eye = imread("./last/eye.bmp", 1);
	Mat skin = imread("./last/skin.bmp", 1);
	int x, y;
	int cnt;
	int R, G, B;
	int H, S, V;

	cnt = 0;
	R = 0;
	G = 0;
	B = 0;
	for (y = 0; y < hair.rows; y++) {
		for (x = 0; x < hair.cols; x++) {
			if (hair.at<Vec3b>(y, x)[0] == 255 && hair.at<Vec3b>(y, x)[1] == 255 && hair.at<Vec3b>(y, x)[2] == 255) {
				cnt++;
			}
			else {
				R += hair.at<Vec3b>(y, x)[2];
				G += hair.at<Vec3b>(y, x)[1];
				B += hair.at<Vec3b>(y, x)[0];

			}
		}
	}
	
	printf("HAIR: R:%d G:%d B:%d \n", R/(hair.rows*hair.cols-cnt), G / (hair.rows*hair.cols - cnt), B / (hair.rows *hair.cols - cnt));
	H = max(R,G,B);
	S=
	cnt = 0;
	R = 0;
	G = 0;
	B = 0;
	for (y = 0; y < eye.rows; y++) {
		for (x = 0; x < eye.cols; x++) {
			if (eye.at<Vec3b>(y, x)[0] == 255 && eye.at<Vec3b>(y, x)[1] == 255 && eye.at<Vec3b>(y, x)[2] == 255) {
				cnt++;
			}
			else {
				R += eye.at<Vec3b>(y, x)[2];
				G += eye.at<Vec3b>(y, x)[1];
				B += eye.at<Vec3b>(y, x)[0];

			}
		}
	}
	printf("EYE: R:%d G:%d B:%d\n", R / (eye.rows * eye.cols - cnt), G / (eye.rows * eye.cols - cnt), B / (eye.rows * eye.cols - cnt));

	cnt = 0;
	R = 0;
	G = 0;
	B = 0;
	for (y = 0; y < skin.rows; y++) {
		for (x = 0; x < skin.cols; x++) {
			if (skin.at<Vec3b>(y, x)[0] == 0 && skin.at<Vec3b>(y, x)[1] == 0 && skin.at<Vec3b>(y, x)[2] == 0) {
				cnt++;
			}
			else {
				R += skin.at<Vec3b>(y, x)[2];
				G += skin.at<Vec3b>(y, x)[1];
				B += skin.at<Vec3b>(y, x)[0];

			}
		}
	}
	printf("SKIN: R:%d G:%d B:%d\n", R / (skin.rows * skin.cols - cnt), G / (skin.rows * skin.cols - cnt), B / (skin.rows * skin.cols - cnt));


}

