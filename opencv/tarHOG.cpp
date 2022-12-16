//#include "main.h"
//
//void tarHOG(float* mag, float* dir, float* tarHOG_descriptor) {
//
//	int height=36, width=36;
//	int x, y, xx, yy;
//	int BLK = 12, binNum = 9;
//	int idx, cnt = 0;
//	float denomi;
//	
//	float* hist = (float*)calloc(binNum, sizeof(float));
//
//
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
//				tarHOG_descriptor[cnt * binNum + yy] = hist[yy];
//			}
//			cnt++;
//		}
//	}
//	free(hist);
//}