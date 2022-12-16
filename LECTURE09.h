#pragma once
#include <vector>
#include <iostream>
#include <fstream>


#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include "ldmarkmodel.h"

using namespace std;
using namespace cv;

void Uniform_LBPdescriptor(Mat input, float* Uniform_LBPhist, int sx, int sy, int j);
float computeSimilarity(float* ref, float* tar);