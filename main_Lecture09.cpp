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


int main()
{
    /*********************
    std::vector<ImageLabel> mImageLabels;
    if(!load_ImageLabels("mImageLabels-test.bin", mImageLabels)){
        mImageLabels.clear();
        ReadLabelsFromFile(mImageLabels, "labels_ibug_300W_test.xml");
        save_ImageLabels(mImageLabels, "mImageLabels-test.bin");
    }
    std::cout << "测试数据一共有: " <<  mImageLabels.size() << std::endl;
    *******************/

    ldmarkmodel modelt;
    std::string modelFilePath = "roboman-landmark-model.bin";//roboman..颇老捞 乐绰 困摹
    while (!load_ldmarkmodel(modelFilePath, modelt)) {
        std::cout << "文件打开错误，请重新输入文件路径." << std::endl;
        std::cin >> modelFilePath;
    }

    cv::VideoCapture mCamera(0);
    if (!mCamera.isOpened()) {
        std::cout << "Camera opening failed..." << std::endl;
        system("pause");
        return 0;
    }
    cv::Mat Image;
    cv::Mat current_shape;
    for (;;) {
        mCamera >> Image;
        modelt.track(Image, current_shape);
        cv::Vec3d eav;
        modelt.EstimateHeadPose(current_shape, eav);
        modelt.drawPose(Image, current_shape, 50);

        int numLandmarks = current_shape.cols / 2;//numLandmarks 罚靛付农 荐
        for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
            int x = current_shape.at<float>(j);
            int y = current_shape.at<float>(j + numLandmarks);
          
            std::stringstream ss;
            ss << j;
          cv::putText(Image, ss.str(), cv::Point(x, y), 0.5, 0.5, cv::Scalar(0, 0, 255));
            cv::circle(Image, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
        }
        cv::imshow("Camera", Image);
        if (27 == cv::waitKey(5)) {
            mCamera.release();
            cv::destroyAllWindows();
            break;
        }
    }

    system("pause");
    return 0;
}

//github俊辑 促款 罐篮 tree 备炼 荤侩窍绰 规过 
//opencv 汲沥茄 visual studio 橇肺璃飘狼 加己芒捞悼
//C/C++狼 老馆 眠啊扼捞宏矾府俊 促款罐篮 src/include甫 眠啊