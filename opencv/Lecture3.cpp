//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//using namespace cv;
//
//void HOG(Mat input, Mat out)
//{
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
//	int height = input.rows;
//	int width = input.cols;
//	int sum1, sum2, deg, idx;
//	float dir;
//	float* hist = (float*)calloc(9, sizeof(float));
//	float* mag = (float*)calloc(height * width, sizeof(float));
//	float* fre = (float*)calloc(height * width, sizeof(float));
//	int x, y;
//	out = input.clone();
//	float S = 0.0;
//	for (y = 1; y < input.size().height - 1; y++)
//	{
//		for (x = 1; x < input.size().width - 1; x++)
//		{
//			sum1 = sum2 = 0;
//			//sum1 x sum2 y
//
//			for (int m = -1; m <= 1; m++)
//			{
//				for (int n = -1; n <= 1; n++)
//				{
//					sum1 += input.at<uchar>(y + m, x + n) * mask1[m + 1][n + 1];
//					sum2 += input.at<uchar>(y + m, x + n) * mask2[m + 1][n + 1];
//				}
//			}
//			mag[y * width + x] = sqrt(sum1 * sum1 + sum2 * sum2);
//			dir = atan2(sum2, sum1);
//			deg = dir * 180.0 / 3.141592;
//			if (deg < 0) deg += 180.0;
//		
//			idx = deg / 20.0;
//			
//			fre[y * width + x] = idx;
//
//		}
//	}
//	for (int y = 0; y <= height - 16; y += 8) {
//		for (int x = 0; x <= width - 16; x += 8) {
//			for (int yy = y; yy < y + 16; yy++) {
//				for (int xx = x; xx < x + 16; xx++) {
//					if (fre[y * width + x] == 0)
//						hist[0] += mag[y * width + x];
//					else if (fre[y * width + x] == 1)
//						hist[1] += mag[y * width + x];
//					else if (fre[y * width + x] == 2)
//						hist[2] += mag[y * width + x];
//					else if (fre[y * width + x] == 3)
//						hist[3] += mag[y * width + x];
//					else if (fre[y * width + x] == 4)
//						hist[4] += mag[y * width + x];
//					else if (fre[y * width + x] == 5)
//						hist[5] += mag[y * width + x];
//					else if (fre[y * width + x] == 6)
//						hist[6] += mag[y * width + x];
//					else if (fre[y * width + x] == 7)
//						hist[7] += mag[y * width + x];
//					else hist[8] += mag[y * width + x];
//				}
//			}
//		}
//	}
//	for (int i = 0; i < 9; i++) {
//
//		S += hist[i];
//	}
//	for (int j = 0; j < 9; j++) {
//
//		printf("%f\n", hist[j] / S);
//	}
//	free(hist);
//	free(mag);
//	free(fre);
//}
//
//void main() {
//	Mat img = imread("test.jpg",IMREAD_COLOR);
//	Mat img2 = img.clone();
//	HOG(img, img2);
//}
//
