#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include  <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/video/tracking.hpp>

#include <vector>
#include <Windows.h>

using namespace cv;
using namespace cv::ml;
using namespace std;

#define PI 3.141592

void LBPdescriptor(Mat input, float* LBPhist, int sx, int sy, int input_width, int input_height);
float computeSimilarity(float* ref, float* tar);
