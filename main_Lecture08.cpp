#include "main.h"

void main() { //¾ó±¼ Å½»ö
	int k, flag = 0;
	float th = 40.0, score;
	VideoCapture capture(0);
	Mat frame;
	if (!capture.isOpened()) {
		printf("Couldn¡¯t open the web camera¡¦\n");
		return;
	}
	CascadeClassifier cascade;
	cascade.load("C:/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml");
	vector<Rect> faces;

	float refLBPhist[256 * 49];
	float tarLBPhist[256 * 49];

	while (1) {
		capture >> frame;
		cascade.detectMultiScale(frame, faces, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));
		if (faces.size() == 1 && flag == 0) {
			Point lb(faces[0].x + faces[0].width, faces[0].y + faces[0].height);
			Point tr(faces[0].x, faces[0].y);
			rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 8, 0);
			
			LBPdescriptor(frame, refLBPhist, faces[0].x, faces[0].y, faces[0].width, faces[0].height);
			flag = 1;
		}

		if (faces.size() > 0 && flag != 0) {	
			for (k = 0; k < faces.size(); k++) {

				LBPdescriptor(frame, tarLBPhist, faces[k].x, faces[k].y, faces[k].width, faces[k].height);
				score = computeSimilarity(refLBPhist, tarLBPhist);
				printf("score: %f\n", score);
				if (score > th) {
					Point lb(faces[k].x + faces[k].width, faces[k].y + faces[k].height);
					Point tr(faces[k].x, faces[k].y);
					rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 8, 0);

				}
				else {
					Point lb(faces[k].x + faces[k].width, faces[k].y + faces[k].height);
					Point tr(faces[k].x, faces[k].y);
					rectangle(frame, lb, tr, Scalar(0, 0, 255), 3, 8, 0);

				}

			}
		}
		
		imshow("Face,frame", frame);
		if (waitKey(30) >= 0)break;
	}
}