#include "main.h"

#define WIN 128 

void LBPdescriptor(Mat input, float* LBPhist, int sx, int sy, int face_width, int face_height) {
	//input은 얼굴 영역을 넣어줘야한다,
	int y,x,yy,xx, height, width;
	height = input.rows;
	width = input.cols;
	float denomi = 0;
	int cnt = 0;
	int val;
	int BLK = WIN / 4;
	float* hist = (float*)calloc(256 * 49, sizeof(float));
	Mat inputGray;
	Mat LBPimage(face_height, face_width, CV_8UC1);
	Mat LBPimageResize(WIN, WIN, CV_8UC1);

	cvtColor(input, inputGray, COLOR_BGR2GRAY);
	for (y = sy; y < sy+face_height; y++) {
		for (x = sx; x < sx+face_width; x++) {
			val = 0;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y - 1, x)) val += 1;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y - 1, x+1)) val += 2;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y , x+1)) val += 4;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x+1)) val += 8;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x)) val += 16;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x-1)) val += 32;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y, x-1)) val += 64;
			if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y- 1, x-1)) val += 128;
			
			LBPimage.at<uchar>(y-sy, x-sx) = val; 
		
		}
	}


	resize(LBPimage, LBPimageResize, Size(WIN,WIN), 1);

	for (y = 0; y <= WIN - BLK; y += BLK / 2) {
		for (x = 0; x <= WIN - BLK; x += BLK / 2) {

			for (yy = 0; yy < 256; yy++) {
				hist[yy] = 0;
			}

			for (yy = y; yy < y + BLK; yy++) {
				for (xx = x; xx < x + BLK; xx++) {
					hist[LBPimageResize.at<uchar>(yy, xx)]++;
					if(LBPimageResize.at<uchar>(yy, xx)>255)printf("나는 255다 크다\n");
				}
			}

			denomi = 0;
			for (yy = 0; yy < 256; yy++) {
				denomi += hist[yy] * hist[yy];
			}
			denomi = sqrt(denomi);

			for (yy = 0; yy < 256; yy++) {
				LBPhist[256 * cnt + yy] = hist[yy] / denomi;
				if (denomi == 0) LBPhist[256 * cnt + yy] = 0;
			}
			cnt++;

		}
	}
	free(hist);
}

