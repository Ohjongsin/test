//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <stdio.h>
//#include <stdlib.h>
//using namespace cv;
//void cornerdetection(Mat input) {
//	// gradient 먼저 계산 이경우 gradient 를 255로 나눔
//	int x, y, xx, yy, xxx, yyy;
//	int height, width;
//	float conv_x, conv_y;
//	float IxIx, IyIy, IxIy, det, tr;
//	float k = 0.04, th = 10000000000 / 2; //Thredhold 값은 구하는 gradient에 따라 바꿀 수
//		float min = 10, max = 0;
//	Scalar c;
//	Point pCenter;
//	int radius = 3;
//	height = input.rows;
//	width = input.cols;
//	float* Ix = (float*)calloc(height * width, sizeof(float));
//	float* Iy = (float*)calloc(height * width, sizeof(float));
//	float* R = (float*)calloc(height * width, sizeof(float));
//	int* cornerMap = (int*)calloc(height * width, sizeof(float));
//	Mat output(height, width, CV_8UC3);
//	Mat cornerness(height, width, CV_8UC1);
//	Mat result(height, width, CV_8UC1);
//	result = input.clone();
//	float* hist = (float*)calloc(9, sizeof(float));
//	float* AB = (float*)calloc(9, sizeof(float));
//	float* FF = (float*)calloc(9, sizeof(float));
//	float* mag = (float*)calloc(height * width, sizeof(float));
//	float* fre = (float*)calloc(height * width, sizeof(float));
//	int deg, idx;
//	float dir, SIM1, SIM2;
//	SIM1 = 0;
//	SIM2 = 0;
//	int P1_x, P1_y, P2_x, P2_y = 0;
//
//	int b_size = 3;
//	int win_size = 3;
//	const int size = 9;
//	int mask1[3][3] = {
//	-1, 0, 1,
//	-2, 0, 2,
//	-1, 0, 1
//	};
//	int mask2[3][3] = {
//	-1, -2, -1,
//	0, 0, 0,
//	1, 2, 1
//	};
//	float sum1, sum2;
//	for (int y = 1; y < height - 1; y++)
//	{
//		for (int x = 1; x < width - 1; x++)
//		{
//			sum1 = sum2 = 0;
//			for (int m = -1; m <= 1; m++)
//			{
//				for (int n = -1; n <= 1; n++)
//				{
//					sum1 += input.at<uchar>(y + m, x + n) * mask1[m + 1][n + 1];
//					sum2 += input.at<uchar>(y + m, x + n) * mask2[m + 1][n + 1];
//				}
//			}
//			Ix[y * width + x] = sum1;
//			Iy[y * width + x] = sum2;
//			mag[y * width + x] = abs(sum1) + abs(sum2);
//			dir = atan2(sum2, sum1);
//			deg = dir * 180 / 3.141592;
//			if (deg < 0) deg += 180.0;
//			idx = deg / 20.0;
//			fre[y * width + x] = idx;
//			output.at<Vec3b>(y, x)[0] = input.at<uchar>(y, x);
//			output.at<Vec3b>(y, x)[1] = input.at<uchar>(y, x);
//			output.at<Vec3b>(y, x)[2] = input.at<uchar>(y, x);
//		}
//	}
//	for (y = 1; y < height - 1; y++) {
//		for (x = 1; x < width - 1; x++) {
//			IxIx = 0;
//			IyIy = 0;
//			IxIy = 0;
//
//			for (yy = y - win_size / 2; yy <= y + win_size / 2; yy++) {
//				for (xx = x - win_size / 2; xx <= x + win_size / 2; xx++) {
//					if (yy >= 0 && yy < height && xx >= 0 && xx < width)
//					{
//						IxIx += Ix[yy * width + xx] * Ix[yy * width + xx];
//						IyIy += Iy[yy * width + xx] * Iy[yy * width + xx];
//						IxIy += Ix[yy * width + xx] * Iy[yy * width + xx];
//					}
//				}
//			}
//			det = IxIx * IyIy - IxIy * IxIy;
//			tr = IxIx + IyIy;
//			R[y * width + x] = det - k * tr * tr;
//			//circle()
//			if (R[y * width + x] > th) {
//				cornerMap[y * width + x] = 1;
//			}
//			if (R[y * width + x] > max) max = R[y * width + x];
//			if (R[y * width + x] < min) min = R[y * width + x];
//
//		}
//	}
//
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if (cornerMap[y * width + x] == 1) {
//				pCenter.x = x;
//				pCenter.y = y;
//				c.val[0] = 0;
//				c.val[1] = 255;
//				c.val[2] = 0;
//				circle(output, pCenter, radius, c, 2, 8, 0); // red circl
//			}
//			cornerness.at<uchar>(y, x) = 255 * (R[y * width + x] - min) / (max - min);
//		}
//	}
//	//for (y = 0; y < height; y++) {
//	//	for (x = 0; x < width / 2; x++) {
//	//		if (y < 8 || y + 8 > height || x < 8 || x + 8 > width / 2) continue;
//	//		if (cornerMap[y * width + x] == 1) {
//	//			P1_x = x;
//	//			P1_y = y;
//	//			for (yy = y - 8; yy <= y + 8; yy++) { //비교 (주) HOG 계산
//	//				for (xx = x - 8; xx <= x + 8; xx++) {
//	//					if (fre[yy * width + xx] == 0)
//	//						hist[0] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 1)
//	//						hist[1] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 2)
//	//						hist[2] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 3)
//	//						hist[3] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 4)
//	//						hist[4] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 5)
//	//						hist[5] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 6)
//	//						hist[6] += mag[yy * width + xx];
//	//					else if (fre[yy * width + xx] == 7)
//	//						hist[7] += mag[yy * width + xx];
//	//					else hist[8] += mag[yy * width + xx];
//	//				} //hist초기화 필요
//	//			}
//	//			for (int j = 0; j < 9; j++) {
//	//				FF[j] = 0;
//	//				P2_x = 0;
//	//				P2_y = 0;
//	//			}
//	//			for (yyy = y; yyy < height; yyy++) {
//
//	//				for (xxx = width / 2 + 1; xxx < width; xxx++) {
//	//					if (yyy == height - 1 && xxx == width - 1) {
//	//						if (P2_x != 0 && P2_y != 0)
//	//							line(result, Point(P1_x, P1_y), Point(P2_x, P2_y), Scalar(100,
//	//								200, 100), 2, 9, 0);
//	//					}
//	//					if (yyy < 8 || yyy + 8 > height || xxx < 8 || xxx + 8 > width)
//	//						continue;
//	//					if (cornerMap[yyy * width + xxx] != 1)continue;
//	//					for (yy = yyy - 8; yy <= yyy + 8; yy++) {
//	//						for (xx = xxx - 8; xx <= xxx + 8; xx++) {
//	//							if (fre[yy * width + xx] == 0)
//	//								AB[0] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 1)
//	//								AB[1] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 2)
//	//								AB[2] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 3)
//	//								AB[3] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 4)
//	//								AB[4] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 5)
//	//								AB[5] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 6)
//	//								AB[6] += mag[yy * width + xx];
//	//							else if (fre[yy * width + xx] == 7)
//	//								AB[7] += mag[yy * width + xx];
//	//							else AB[8] += mag[yy * width + xx];
//	//						}
//	//					}
//	//					SIM1, SIM2 = 0;
//
//	//					/*for (int i = 0; i < 9; i++) {
//	//					SIM1 += abs(AB[i] - hist[i]);
//	//					SIM2 += abs(FF[i] - hist[i]);
//	//					}
//	//					if (SIM1 < SIM2) {*/
//
//	//					for (int j = 0; j < 9; j++) {
//	//						SIM1 += abs(hist[j] / AB[j]);
//	//						SIM2 += abs(hist[j] / FF[j]);
//	//						P2_x = xxx;
//	//						P2_y = yyy;
//	//					}
//	//					if (SIM1 < SIM2) {
//	//						for (int i = 0; i < 9; i++) {
//	//							FF[i] = AB[i];
//	//							P2_x = xxx;
//	//							P2_y = yyy;
//	//						}
//	//					}
//	//					/* for (int i = 0; i < 9; i++) {
//
//	//					if (abs(AB[i] - hist[i]) > 1000000000|| abs(AB[i] - hist[i]) >
//	//				   abs(FF[i] - hist[i])) break;
//	//					FF[i] = AB[i];
//	//					P2_x = xxx;
//	//					P2_y = yyy;
//
//	//					}*/
//	//					/*for (int i = 0; i < 9; i++) {
//	//					if (abs(AB[i] - hist[i]) < 1000000) SIM1+=1;
//
//	//					}
//
//	//					if (SIM1 > max) {
//	//					max = SIM1;
//
//	//					P2_x = xxx;
//	//					P2_y = yyy;
//	//					}*/
//
//
//	//				}//2번째 for문
//	//			} //2번째 for문
//
//
//
//	//		}
//	//	}//첫번째 for
//	//}//첫번째 for
//	imwrite("./images/result.bmp", output);
//	imwrite("./images/result1.bmp", cornerness);
//	imwrite("./images/fresult.bmp", result);
//	free(hist);
//	free(AB);
//	free(FF);
//	free(mag);
//	free(fre);
//	free(cornerMap);
//	free(R);
//	free(Iy);
//	free(Ix);
//}
//void main() {
//
//	Mat imgColor = imread("test.jpg",IMREAD_COLOR);
//	cornerdetection(imgColor);
//}