// color to gray in specific region
// //#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//using namespace cv;
//
//void main()
//{
//    int x, y, centerX, centerY, BLK;
//    int startX, endX, startY, endY;
//    Mat img = imread("test.jpg", IMREAD_COLOR);
//    int width = img.cols;
//    int height = img.rows;
//    Mat Result = img.clone();
//    do
//    {
//        printf("Input your center position and window size : ");
//        scanf_s("%d %d %d", &centerX, &centerY, &BLK);
//
//    } while (!(centerX >= 0 && centerY >= 0 && BLK > 0));
//
//    startX = (centerX - BLK < 0) ? 0 : centerX - BLK;
//    endX = (centerX + BLK > width) ? width : centerX + BLK;
//    startY = (centerY - BLK < 0) ? 0 : centerY - BLK;
//    endY = (centerY + BLK > height) ? height : centerY + BLK;
//    for (y = startY; y < endY; y++)
//    {
//        for (x = startX; x < endX; x++)
//        {
//            int gray = (img.at<Vec3b>(y, x)[2] + img.at<Vec3b>(y, x)[1] + img.at<Vec3b>(y, x)[0]) / 3;
//
//            Result.at<Vec3b>(y, x)[2] = gray;
//            Result.at<Vec3b>(y, x)[1] = gray;
//            Result.at<Vec3b>(y, x)[0] = gray;
//        }
//    }
//    //imshow("color", img);
//    imwrite("EE02_convert_color_to_gray.bmp", Result);
//    printf("finished\n");
//    waitKey(5000);
//}


