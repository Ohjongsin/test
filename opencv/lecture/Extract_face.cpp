#include "main.h"

/*void Extract_face(Mat input, Mat maskimg)*/
void main() {
	Mat input = imread("image.bmp",1);
	Mat maskimg = imread("maskimg.bmp", 1);
	int height = input.rows;
	int width = input.cols;
	int x, y;

	Mat mask = Mat::ones(height, width, CV_8UC1) * GC_PR_BGD;
	Rect rectangle(0, 0, width - 1, height - 1);
	Mat result;
	Mat bg, fg;
	/*Mat eye;
	int flag = 0;
	printf("Exstart\n");
	*//*imwrite("image.bmp", input);
	imwrite("maskimg.bmp", maskimg);*/

	//CascadeClassifier cascade;
	//cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_lefteye_2splits.xml");
	//vector<Rect> eyes;
	//cascade.detectMultiScale(maskimg, eyes, 1.1, 3); //크기 조정, 경계원에 맞추기

	//for (int i = 0; i < eyes.size(); i++) {
	//	Point lb(eyes[i].x + eyes[i].width, eyes[i].y + eyes[i].height);
	//	Point tr(eyes[i].x, eyes[i].y);
	//	if (flag == 0) eye = input(Range(tr.y, lb.y), Range(tr.x, lb.x));
	//}


	//imwrite("./images/eye.bmp", eye);
	//imwrite("./images/except_skin.bmp", input);
		/*Rect rectangle(204,134,416,346);

		Mat result;
		Mat bg, fg;
		grabCut(image, result, rectangle, bg, fg, 5, GC_INIT_WITH_RECT);
		compare(result, GC_PR_FGD, result, CMP_EQ);
		Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255));
		imwrite("result.bmp", result);
		image.copyTo(foreground, result);
		imwrite("extract_face.bmp", foreground);*/

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (x < 204 || x>416 || y < 90 || y>390) {
				input.at<Vec3b>(y, x)[0] = 255;
				input.at<Vec3b>(y, x)[1] = 255;
				input.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
		
		for (y = 0; y < height; y++)
		{
			for (x = 0; x < width; x++)
			{
				if (maskimg.at<Vec3b>(y, x)[0] == 255 && maskimg.at<Vec3b>(y, x)[1] == 0 && maskimg.at<Vec3b>(y, x)[2] == 255)
				{
					mask.at<uchar>(y, x) = GC_BGD;	//gcbgd 내가 칠한것 배경
				}
				if (maskimg.at<Vec3b>(y, x)[0] == 0 && maskimg.at<Vec3b>(y, x)[1] == 255 && maskimg.at<Vec3b>(y, x)[2] == 0)
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

        imwrite("./images/result2.bmp", final_result);
	     /*Extract_color(final_result,input);
		*/
	/*	imwrite("./images/mask.bmp", mask);
		imwrite("./images/mask_result.bmp", mask_result);
		*/

		printf("Exend\n");

		
}
