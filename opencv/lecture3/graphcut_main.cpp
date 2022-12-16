#include "main.h"



void main()
{
	/*Mat image = imread("input.jpg");
	Rect rectangle(10, 100, 380, 180);
	Mat result;
	Mat bg, fg;
	grabCut(image, result, rectangle, bg, fg, 5, GC_INIT_WITH_RECT);
	compare(result, GC_PR_FGD, result, CMP_EQ);
	Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255));
	image.copyTo(foreground, result);
	imshow("Foreground", foreground);
	waitKey(0);*/


	Mat input = imread("input.jpg");
	Mat maskimg = imread("mask1.bmp");

	grabcutwithmask(input, maskimg);


}


