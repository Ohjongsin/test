#include "LECTURE09.h"

int main() { //倔奔 沤祸
	int k, flag = 0;
	float th = 0.4, score;
	
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml");
	vector<Rect> faces;
	
	float refLBPhist_uniform[59 * 49 * 41] = {0};
	float tarLBPhist_uniform[59 * 49 * 41] = {0};
	
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
		cascade.detectMultiScale(Image, faces, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));
		if (faces.size() == 1 && flag == 0) {
			
			for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
				int x = current_shape.at<float>(j);
				int y = current_shape.at<float>(j + numLandmarks);
				//LBP 
				
				if(j>26 && j<67)Uniform_LBPdescriptor(Image, refLBPhist_uniform, x, y, j);

				cv::circle(Image, cv::Point(x, y), 2, cv::Scalar(0, 255, 0), -1);
			}
			flag = 1;
		
		}

		if (faces.size() > 0 && flag != 0) {

			for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
				int x = current_shape.at<float>(j);
				int y = current_shape.at<float>(j + numLandmarks);
				//LBP 
				if (j > 26 && j < 67)Uniform_LBPdescriptor(Image, tarLBPhist_uniform, x, y, j);
			}
				score = computeSimilarity(refLBPhist_uniform, tarLBPhist_uniform);
				printf("score: %f \n",score);
				if (score > th) {
					for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
						int x = current_shape.at<float>(j);
						int y = current_shape.at<float>(j + numLandmarks);
						cv::circle(Image, cv::Point(x, y), 2, cv::Scalar(0, 255, 0), -1);
					}
				}
				else {
					for (int j = 0; j < numLandmarks; j++) { //x,y rk landmark point
						int x = current_shape.at<float>(j);
						int y = current_shape.at<float>(j + numLandmarks);
						cv::circle(Image, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
					}

				}


			
			
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