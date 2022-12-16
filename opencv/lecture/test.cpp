#include "main.h"


void main() {

	Mat input = imread("image.bmp", 1);
	Mat ss = imread("skinimg.bmp", 1);
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
	add(input, Scalar(0), sk, hsv);
	imwrite("./test/hsvskin.bmp", sk);
	/*for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (sk.at<Vec3b>(y, x)[0] != 0) {
				ss.at<Vec3b>(y, x)[0] = 255;
				ss.at<Vec3b>(y, x)[1] = 255;
				ss.at<Vec3b>(y, x)[2] = 255;

			}
		}
	}*/
	imwrite("e.bmp", ss);
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_lefteye_2splits.xml");
	vector<Rect> eyes;
	cascade.detectMultiScale(input, eyes, 1.1, 3); //크기 조정, 경계원에 맞추기

	for (int i = 0; i < eyes.size(); i++) {
		Point lb(eyes[i].x + eyes[i].width, eyes[i].y + eyes[i].height);
		Point tr(eyes[i].x, eyes[i].y);
		rectangle(input, lb, tr, Scalar(255, 255, 255), 1,0);
		if (flag == 0) {
			eye = ss(Range(tr.y, lb.y), Range(tr.x, lb.x));
			flag = 1;
		}
	}
	Mat eyeG;
	cvtColor(eye, eyeG, COLOR_BGR2GRAY);
	
	for (int i = 0; i<eyeG.rows; i++) {
		for (int j = 0; j<eyeG.cols; j++) {
			
			if (eyeG.at<uchar>(i, j) > 25 || i< eyeG.rows/3) {
				eyeG.at<uchar>(i, j) = 255;
			}

		}
	}
	for (int i = 0; i < eyeG.rows; i++) {
		for (int j = 0; j < eyeG.cols; j++) {
			if (eyeG.at<uchar>(i, j) ==255 ) {
				eye.at<Vec3b>(i, j)[0] = 255;
				eye.at<Vec3b>(i, j)[1] = 255;
				eye.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	imwrite("./test/eyeG.bmp", eyeG);
	imwrite("./test/eye.bmp", eye);
	imwrite("./test/except_skin.bmp", input);

	//int height = input.rows;
	//	int width = input.cols;
	//	int x, y;

	//	for (y = 0; y < height; y++) {
	//		for (x = 0; x < width; x++) {
	//			if (y> 80 || sk.at<Vec3b>(y, x)[0] != 255) {
	//				hair.at<Vec3b>(y, x)[0] = 255;
	//				hair.at<Vec3b>(y, x)[1] = 255;
	//				hair.at<Vec3b>(y, x)[2] = 255;

	//			}
	//		}
	//	}

	//	CascadeClassifier cascade;
	//	cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_eye.xml");
	//	vector<Rect> eyes;
	//	cascade.detectMultiScale(input, eyes, 1.1, 3); //크기 조정, 경계원에 맞추기
	//	
	//	for (int i = 0; i < eyes.size(); i++) {
	//		Point lb(eyes[i].x + eyes[i].width, eyes[i].y + eyes[i].height);
	//		Point tr(eyes[i].x, eyes[i].y);
	//		printf("lb.x:%d lb.y:%d\n tr.x:%d tr.y:%d\n", lb.x, lb.y, tr.x, tr.y);
	//		rectangle(input, lb, tr, Scalar(255, 255, 255), 3, -1, 0);
	//	}
	//	for (y = 0; y < height; y++) {
	//		for (x = 0; x < width; x++) {
	//			if (y > 300) {
	//				input.at<Vec3b>(y, x)[0] = 255;
	//				input.at<Vec3b>(y, x)[1] = 255;
	//				input.at<Vec3b>(y, x)[2] = 255;
	//			}
	//		}
	//	}
	//	imwrite("./test/hair_eye.bmp", input);
	//	imwrite("./test/hair.bmp", hair);

}