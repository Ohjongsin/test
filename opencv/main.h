#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include  <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;
using namespace cv::ml;
using namespace std;

#define PI 3.141592

void refHOG(Mat input, float* refHOG_descriptor);
void tarHOG(float* testMag, float* testDir, float* tarHOG_descriptor);
void searFaces(Mat input, float* refHOG_descriptor);
float computeSimilarity(float* ref, float* tar);