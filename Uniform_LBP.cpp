#include "main.h"

#define WIN 16 //uniform_LBP의 크기가 16*16

void Uniform_LBPdescriptor(Mat input, float* Uniform_LBPhist, int sx, int sy, int count) {
	//input은 얼굴 영역을 넣어줘야한다,
	int y, x, yy, xx;
	float denomi = 0;
	int cnt = 0;
	int BLK = WIN / 4;
	int val;
	float* LBPhist = (float*)calloc(59 * 49, sizeof(float));
    float* hist = (float*)calloc(59 * 1, sizeof(float)); 
	int j = count - 27;
	Mat inputGray;
	Mat LBPimage(WIN, WIN, CV_8UC1);

	const char lookup[256] = {
0, 1, 2, 3, 4, 58, 5, 6, 7, 58, 58, 58, 8, 58, 9, 10,
11, 58, 58, 58, 58, 58, 58, 58, 12, 58, 58, 58, 13, 58, 14, 15,
16, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
17, 58, 58, 58, 58, 58, 58, 58, 18, 58, 58, 58, 19, 58, 20, 21,
22, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
23, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
24, 58, 58, 58, 58, 58, 58, 58, 25, 58, 58, 58, 26, 58, 27, 28,
29, 30, 58, 31, 58, 58, 58, 32, 58, 58, 58, 58, 58, 58, 58, 33,
58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 34,
58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58,
58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 35,
36, 37, 58, 38, 58, 58, 58, 39, 58, 58, 58, 58, 58, 58, 58, 40,
58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 58, 41,
42, 43, 58, 44, 58, 58, 58, 45, 58, 58, 58, 58, 58, 58, 58, 46,
47, 48, 58, 49, 58, 58, 58, 50, 51, 52, 58, 53, 54, 55, 56, 57 };

	cvtColor(input, inputGray, COLOR_BGR2GRAY);

	for (y = sy - WIN / 2; y < sy + WIN / 2; y++) {
		for (x = sx - WIN / 2; x < sx + WIN / 2; x++) {

			val = 0;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y - 1, x)) val += 1;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y - 1, x+1)) val += 2;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y , x+1)) val += 4;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x+1)) val += 8;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x)) val += 16;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y+1, x-1)) val += 32;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y, x-1)) val += 64;
						if (inputGray.at<uchar>(y, x) < inputGray.at<uchar>(y- 1, x-1)) val += 128;
						
						LBPimage.at<uchar>(y - sy + WIN / 2, x - sx + WIN / 2) = lookup[val];
			
		}
	}




	for (y = 0; y <= WIN - BLK; y += BLK / 2) {
		for (x = 0; x <= WIN - BLK; x += BLK / 2) {

			for (yy = 0; yy < 59; yy++) {
				hist[yy] = 0;
			}

			for (yy = y; yy < y + BLK; yy++) {
				for (xx = x; xx < x + BLK; xx++) {
					hist[LBPimage.at<uchar>(yy, xx)]++;
				}
			}

			denomi = 0;
			for (yy = 0; yy < 59; yy++) {
				denomi += hist[yy] * hist[yy];
			}
			denomi = sqrt(denomi);

			for (yy = 0; yy < 59; yy++) {
				LBPhist[59 * cnt + yy] = hist[yy] / denomi; // j 추가 해서 연속으로 저장
				if (denomi == 0) LBPhist[59 * cnt + yy] = 0;
	
			}
			cnt++;

		}
	}
	
	for (int k = 0; k < 59 * 49; k++) {
		Uniform_LBPhist[59 * 49 * j + k] = LBPhist[k];
	}

    free(LBPhist);
	free(hist);
	
}



