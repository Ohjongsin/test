#include "main.h"

void main() { //얼굴 탐색
	int flag = 0;
	VideoCapture capture(0);
	Mat frame;
	if (!capture.isOpened()) {
		printf("Couldn’t open the web camera…\n");
		return;
	}
	
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml");
	vector<Rect> faces;
	Mat img_circle;
	while (1) {
		capture >> frame;
		cascade.detectMultiScale(frame, faces, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(100, 100)); //크기 조정, 경계원에 맞추기
		img_circle = frame.clone();
		//logo.copyTo(imageROI, mask);
		circle(img_circle, Point(310, 240), 150, Scalar(255, 0, 255), 3, 8, 0);
		if (faces.size() == 1) {
			Point lb(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
			Point tr(faces[0].x, faces[0].y);
			
			printf("lb.x:%d lb.y:%d\n tr.x:%d tr.y:%d\n", lb.x, lb.y, tr.x, tr.y);
			int sx, sy, x, y;
			sx = (lb.x + tr.x) / 2;
			sy = (lb.y + tr.y) / 2;
			line(img_circle, Point(sx,tr.y-10), Point(sx, lb.y +10), Scalar(0, 255, 0), 3, 8, 0);
			line(img_circle, Point(tr.x+13, sy), Point(lb.x-13, sy), Scalar(0, 255, 0), 3, 8, 0);
			/*rectangle(img_circle, lb, tr, Scalar(0, 255, 0), 3, 8, 0);*/
			
			
			if (flag == 0 && tr.x > 204 && tr.y > 134 && lb.x < 416 && lb.y < 346) {

				Extract_face(frame, img_circle);
				break;
			}

		}

		imshow("Face", img_circle);
		if (waitKey(30) >= 0) break;
	}
}
