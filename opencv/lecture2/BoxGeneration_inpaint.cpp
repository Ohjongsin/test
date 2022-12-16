#include "main.h"
void BoxGernerationandinpaint(Mat input, Mat input_gray, float* cornerPos) {
	
	int x, y;
	int height, width, margin = 10;
	int min_x = 10000, min_y = 10000, max_x = -1, max_y = -1;

	height = input.rows;
	width = input.cols;

	Mat textBox(height, width, CV_8UC1);
	Mat result(height, width, CV_8UC3);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (cornerPos[y * width + x] == 1 && x > margin && x<width - margin && y>margin && y < height - margin) {
				if (max_x < x) max_x = x;
				if (min_x > x) min_x = x;
				if (max_y < y) max_y = y;
				if (min_y > y) min_y = y;
			}
			textBox.at<uchar>(y, x) = 0;
		}
	}

	for (y = min_y; y < max_y; y++) {
		for (x = min_x; x < max_x; x++) {
			textBox.at<uchar>(y, x) = 255;
		}
	}
		
		inpaint(input, textBox, result, 3, INPAINT_TELEA);
		
		imwrite("/images/RESULT.bmp", result);

}