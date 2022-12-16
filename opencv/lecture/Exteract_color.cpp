#include "main.h"


void Extract_color(Mat input, Mat maskimg){
	/*void main()*/
	/*Mat input = imread("cutimg.bmp",1);*/
	int height = input.rows;
	int width = input.cols;
	int x, y;
	Mat eye = input.clone();

	Mat sk;
		Mat hsv;
	
	
	
		cvtColor(input, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(0, 48, 80), Scalar(20, 255, 255), hsv);
		imwrite("./test/hsvtest.bmp", hsv);
		sk = (hsv.size(), CV_8UC3, Scalar(0));
		add(input, Scalar(0), sk, hsv);
		imwrite("./test/hsvskin.bmp", sk);
	/*Mat skin;
	skin = input.clone();
		
	Mat hlsimg(height, width, CV_8UC3);
			
	cvtColor(input, hlsimg, COLOR_BGR2HLS);
	vector<Mat> hls_img(3);
	split(hlsimg, hls_img);

	for (y = 0; y < hlsimg.rows; y++) {
		for (x = 0; x < hlsimg.cols; x++) {
			uchar H = hlsimg.at<Vec3b>(y, x)[0];
			uchar L = hlsimg.at<Vec3b>(y, x)[1];
			uchar S = hlsimg.at<Vec3b>(y, x)[2];

			double LS_ratio = ((double)L) / ((double)S);
			bool skin_pixel = (S >= 50) && (LS_ratio > 0.5) && (LS_ratio < 3.0) && ((H <= 14) || (H >= 165));

			if (skin_pixel == false) {
				skin.at<Vec3b>(y, x)[0] = 255;
				skin.at<Vec3b>(y, x)[1] = 255;
				skin.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}

	imwrite("./images/skin.bmp", skin);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			if (skin.at<Vec3b>(y, x)[0] != 255) {
				input.at<Vec3b>(y, x)[0] = 255;
				input.at<Vec3b>(y, x)[1] = 255;
				input.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}
	imwrite("./images/exept_skin.bmp", input);*/

	

	//std::vector<ImageLabel> mImageLabels;
	//    if(!load_ImageLabels("mImageLabels-test.bin", mImageLabels)){
	//        mImageLabels.clear();
	//        ReadLabelsFromFile(mImageLabels, "labels_ibug_300W_test.xml");
	//        save_ImageLabels(mImageLabels, "mImageLabels-test.bin");
	//    }
	//    std::cout << "测试数据一共有: " <<  mImageLabels.size() << std::endl;
	//  
	//
	//    ldmarkmodel modelt;
	//    std::string modelFilePath = "roboman-landmark-model.bin";//roboman..颇老捞 乐绰 困摹
	//    while (!load_ldmarkmodel(modelFilePath, modelt)) {
	//        std::cout << "文件打开错误，请重新输入文件路径." << std::endl;
	//        std::cin >> modelFilePath;
	//    }
	//
	//  
	//    
	//    cv::Mat current_shape;
	//   
	//        
	//        modelt.track(input, current_shape);
	//        cv::Vec3d eav;
	//        modelt.EstimateHeadPose(current_shape, eav);
	//        modelt.drawPose(input, current_shape, 50);
	//
	//        int numLandmarks = current_shape.cols / 2;//numLandmarks 罚靛付农 荐
	//        for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
	//            int x = current_shape.at<float>(j);
	//            int y = current_shape.at<float>(j + numLandmarks);
	//          
	//            std::stringstream ss;
	//            ss << j;
	//         /* cv::putText(input, ss.str(), cv::Point(x, y), 0.5, 0.5, cv::Scalar(0, 0, 255));
	//            cv::circle(input, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);*/
	//        }
	//        
	//		imwrite("./images/SDM.bmp", input);
	//
	    
	
	
}