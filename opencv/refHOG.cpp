//#include "main.h"
//
//void refHOG(Mat input, float* refHOG_descriptor) {
//
//	int x, y, xx, yy;
//	int height = input.rows;
//	int width = input.cols;
//	int BLK = width / 3, binNum = 9;
//	int idx, cnt = 0;
//	float conv_x, conv_y;
//	float denomi;
//	float* mag = (float*)calloc(height * width, sizeof(float));
//	float* dir = (float*)calloc(height * width, sizeof(float));
//	float* hist = (float*)calloc(binNum, sizeof(float));
//	int mask_x[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
//	int mask_y[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
//
//	Mat result(height, width, CV_8UC1);
//
//    // compute magnitude and direction
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			conv_x = 0;
//			conv_y = 0;
//
//			//inner product
//			for (yy = y - 1; yy <= y + 1; yy++) {
//				for (xx = x - 1; xx <= x + 1; xx++) {
//					if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
//						conv_x += input.at<uchar>(yy, xx) * mask_x[(yy - (y - 1)) * 3 + (xx - (x - 1))];
//						conv_y += input.at<uchar>(yy, xx) * mask_y[(yy - (y - 1)) * 3 + (xx - (x - 1))];
//					}
//
//				}
//			}
//
//			conv_x /= 9.0;
//			conv_y /= 9.0;
//
//			mag[y * width + x] = sqrt(conv_x * conv_x + conv_y * conv_y);
//			dir[y * width + x] = atan2(conv_y, conv_x);
//
//			dir[y * width + x] = dir[y * width + x] * 180 / PI; // 
//			if (dir[y * width + x] < 0)dir[y * width + x] += 180.0;
//		}
//	}
//
//	//computr HOG
//	for (y = 0; y <= height - BLK; y += BLK / 2) {
//		for (x = 0; x <= width - BLK; x += BLK / 2) {
//
//			for (yy = 0; yy < binNum; yy++)
//				hist[yy] = 0;
//
//			for (yy = y; yy < y + BLK; yy++) {
//				for (xx = x; xx < x + BLK; xx++) {
//					idx = dir[yy * width + xx] / 20.0;
//					hist[idx] += mag[yy * width + xx];
//				}
//			}
//			//normalization
//			denomi = 0;
//			for (yy = 0; yy < binNum; yy++) {
//				denomi += hist[yy] * hist[yy];
//			}
//			for (yy = 0; yy < binNum; yy++) {
//				hist[yy] /= sqrt(denomi);
//				if (denomi == 0)
//					hist[yy] = 0;
//
//				refHOG_descriptor[cnt * binNum + yy] = hist[yy];
//			}
//			cnt++;
//		}
//	}
//
//	free(mag);
//	free(dir);
//	free(hist);
//}