#include "main.h"

void grabcutwithmask(Mat input, Mat maskimg)
{



	int y, x;
	int height = input.rows;
	int width = input.cols;
	Mat mask = Mat::ones(height, width, CV_8UC1) * GC_PR_BGD;
	Rect rectangle(0, 0, width - 1, height - 1);
	Mat result;
	Mat bg, fg;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (maskimg.at<Vec3b>(y, x)[0] == 255 && maskimg.at<Vec3b>(y, x)[1] == 0 && maskimg.at<Vec3b>(y, x)[2] == 0)
			{
				mask.at<uchar>(y, x) = GC_BGD;	//gcbgd 내가 칠한것 배경
			}
			if (maskimg.at<Vec3b>(y, x)[0] == 0 && maskimg.at<Vec3b>(y, x)[1] == 0 && maskimg.at<Vec3b>(y, x)[2] == 255)
			{
				mask.at<uchar>(y, x) = GC_FGD;	//gcfgd 내가 칠한것 전경
			}


		}
	}

	Mat final_result = Mat::zeros(height, width, CV_8UC3);
	Mat mask_result = Mat::zeros(height, width, CV_8UC1);

	final_result = input.clone();

	grabCut(input, mask, rectangle, bg, fg, 8, GC_INIT_WITH_MASK);	//각 인수에 대한 이해 필요

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (mask.at<uchar>(y, x) == GC_FGD || mask.at<uchar>(y, x) == GC_PR_FGD)
			{
				mask_result.at<uchar>(y, x) = 255;

			}
			else {
				final_result.at<Vec3b>(y, x)[0] = 255;
				final_result.at<Vec3b>(y, x)[1] = 255;
				final_result.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
	imwrite("./images/result.bmp", final_result);
	imwrite("./images/mask.bmp", mask);
	imwrite("./images/mask_result.bmp", mask_result);
}