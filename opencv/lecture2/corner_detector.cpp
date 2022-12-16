#include "main.h"

void corner_detector(Mat input, float* R) {

	int x, y, xx, yy;
	int height = input.rows;
	int width = input.cols;
	float conv_x, conv_y;
	float denomi;

	Scalar c;
	Point pCenter;
	Mat output(height, width, CV_8UC3);
	Mat cornerness(height, width, CV_8UC1);
	float IxIx, IyIy, IxIy, det, tr;
	float* Ix = (float*)calloc(height * width, sizeof(float));
	float* Iy = (float*)calloc(height * width, sizeof(float));
	
	int* cornerMap = (int*)calloc(height * width, sizeof(float));
	int win_size = 3;
	int radius = 3;
	float k = 0.04, th = 10;
	float min = 10, max = 0;

	float* mag = (float*)calloc(height * width, sizeof(float));
	float* dir = (float*)calloc(height * width, sizeof(float));
	
	int mask_x[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	int mask_y[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };

	Mat result(height, width, CV_8UC1);

	// compute magnitude and direction
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			conv_x = 0;
			conv_y = 0;

			//inner product
			for (yy = y - 1; yy <= y + 1; yy++) {
				for (xx = x - 1; xx <= x + 1; xx++) {
					if (yy >= 0 && yy < height && xx >= 0 && xx < width) {
						conv_x += input.at<uchar>(yy, xx) * mask_x[(yy - (y - 1)) * 3 + (xx - (x - 1))];
						conv_y += input.at<uchar>(yy, xx) * mask_y[(yy - (y - 1)) * 3 + (xx - (x - 1))];
					}

				}
			}
			
			conv_x /= 9.0;
			conv_y /= 9.0;
			Ix[y * width + x] = conv_x;
			Iy[y * width + x] = conv_y;
			mag[y * width + x] = sqrt(conv_x * conv_x + conv_y * conv_y);
			dir[y * width + x] = atan2(conv_y, conv_x);

			dir[y * width + x] = dir[y * width + x] * 180 / PI; // 
			if (dir[y * width + x] < 0)dir[y * width + x] += 180.0;

			output.at<Vec3b>(y, x)[0] = input.at<uchar>(y, x);
			output.at<Vec3b>(y, x)[1] = input.at<uchar>(y, x);
			output.at<Vec3b>(y, x)[2] = input.at<uchar>(y, x);
		}
	}

	for (y = 1; y < height - 1; y++) {
		for (x = 1; x < width - 1; x++) {
			IxIx = 0;
			IyIy = 0;
			IxIy = 0;

			for (yy = y - win_size / 2; yy <= y + win_size / 2; yy++) {
				for (xx = x - win_size / 2; xx <= x + win_size / 2; xx++) {
					if (yy >= 0 && yy < height && xx >= 0 && xx < width)
					{
						IxIx += Ix[yy * width + xx] * Ix[yy * width + xx];
						IyIy += Iy[yy * width + xx] * Iy[yy * width + xx];
						IxIy += Ix[yy * width + xx] * Iy[yy * width + xx];
					}
					else R[y * width + x] = 0;
				}
			}
			det = IxIx * IyIy - IxIy * IxIy;
			tr = IxIx + IyIy;
			R[y * width + x] = det - k * tr * tr;
			
			if (R[y * width + x] > th) {
				cornerMap[y * width + x] = 1;
			}
			if (R[y * width + x] > max) max = R[y * width + x];
			if (R[y * width + x] < min) min = R[y * width + x];
		}
	}
	printf("max: %f\n min: %f\n", max, min);
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (cornerMap[y * width + x] == 1) {
				pCenter.x = x;
				pCenter.y = y;
				c.val[0] = 0;
				c.val[1] = 255;
				c.val[2] = 0;
				circle(output, pCenter, radius, c, 2, 8, 0); // red circl
			}
			cornerness.at<uchar>(y, x) = 255 * (R[y * width + x] - min) / (max - min);
		}
	}
	
	imwrite("./images/result.bmp", output);
	imwrite("./images/result1.bmp", cornerness);
	free(mag);
	free(dir);
	free(cornerMap);
	
	free(Iy);
	free(Ix);
}