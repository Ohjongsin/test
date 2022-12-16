//#include "main.h"
//
//void searFaces(Mat input, float* refHOG_descriptor) {
//	int x, y, xx, yy;
//	int height = input.rows;
//	int width = input.cols;
//	int WIN = 36, binNum = 9;
//	int idx, cnt = 0;
//	float conv_x, conv_y;
//	float denomi;
//	float min = 10000000000, max = -1;
//	float* mag = (float*)calloc(height * width, sizeof(float));
//	float* dir = (float*)calloc(height * width, sizeof(float));
//	float* testMag = (float*)calloc(WIN * WIN, sizeof(float));
//	float* testDir = (float*)calloc(WIN * WIN, sizeof(float));
//	float* tarHOG_descriptor = (float*)calloc(binNum * 25, sizeof(float));
//	float* simMap = (float*)calloc(height * width, sizeof(float));
//
//	int mask_x[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
//	int mask_y[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
//
//	Mat result(height, width, CV_8UC1);
//
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			conv_x = 0;
//			conv_y = 0;
//
//			for (yy = y - 1; yy <= y + 1; yy++) {
//				for (xx = x - 1; xx <= x + 1; xx++) {
//					if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
//						conv_x += input.at<uchar>(yy, xx) * mask_x[(yy - (y - 1)) * 3 + (xx - (x - 1))];
//						conv_y += input.at<uchar>(yy, xx) * mask_y[(yy - (y - 1)) * 3 + (xx - (x - 1))];
//					}
//
//				}
//			}
//			conv_x /= 9.0;
//			conv_y /= 9.0;
//
//			mag[y * width + x] = sqrt(conv_x * conv_x + conv_y * conv_y);
//			dir[y * width + x] = atan2(conv_y, conv_x);
//
//			dir[y * width + x] = dir[y * width + x] * 180 / PI;
//			if (dir[y * width + x] < 0)dir[y * width + x] += 180.0;
//
//
//			/*faceResult.at<Vec3b>(y, x)[0] = input.at<uchar>(y, x);
//			faceResult.at<Vec3b>(y, x)[1] = input.at<uchar>(y, x);
//			faceResult.at<Vec3b>(y, x)[2] = input.at<uchar>(y, x);*/
//		}
//	}
//
//	//searching faces
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//
//			idx = 0;
//
//			for (yy = y - WIN / 2; yy < y + WIN / 2; yy++) {
//				for (xx = x - WIN / 2; xx < x + WIN / 2; xx++) {
//					if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
//						testMag[idx] = mag[yy * width + xx];
//						testDir[idx] = dir[yy * width + xx];
//						idx++;
//					}
//				
//				}
//			}
//			tarHOG(testMag, testDir, tarHOG_descriptor);
//
//			simMap[y * width + x] = computeSimilarity(refHOG_descriptor, tarHOG_descriptor);
//			if (min > simMap[y * width + x])min = simMap[y * width + x];
//			if (max < simMap[y * width + x])max = simMap[y * width + x];
//		}
//	}
//	
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			result.at<uchar>(y, x) = 255 * (simMap[y * width + x] - min) / (max - min);
//		}
//	}
//	
//	Mat img = imread("face_tar.bmp", 1); // image read (color)
//	for (y = 0; y < height; y++) {
//		for (x = 0; x < width; x++) {
//			if ((255 * (simMap[y * width + x] - min) / (max - min)) > 40) {
//				Point lb(x-16, y-16);
//				Point tr(x + 16, y + 16);
//				rectangle(img, lb, tr, Scalar(0, 255, 0), 3, 8, 0);
//				printf("%f x:%d, y:%d\n", 255 * (simMap[y * width + x] - min) / (max - min), x, y);
//				x += 20;
//			}
//			
//		}
//	}
//	imshow("Face", img);
//	waitKey(50000);
//	imwrite("./images/similarityMap.bmp", result);
//
//	free(mag);
//	free(dir);
//	free(testMag);
//	free(testDir);
//	free(tarHOG_descriptor);
//	free(simMap);
//}