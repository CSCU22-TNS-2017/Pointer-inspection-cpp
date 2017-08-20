//#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//#include <Windows.h>
//#include <conio.h>
//
//using namespace cv;
//using namespace std;
//Mat orig;
//void onMouse(int event, int x, int y, int flags, void* param)
//{
//	char text[100];
//	Mat img2, img3;
//
//	img2 = orig.clone();
//
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		Vec3b p = img2.at<Vec3b>(y, x);
//		sprintf(text, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
//	}
//	else if (event == CV_EVENT_RBUTTONDOWN)
//	{
//		cvtColor(orig, img3, CV_BGR2HSV);
//		Vec3b p = img3.at<Vec3b>(y, x);
//		sprintf(text, "H=%d, S=%d, V=%d", p[0], p[1], p[2]);
//	}
//	else
//		sprintf(text, "x=%d, y=%d", x, y);
//
//	putText(img2, text, Point(5, 15), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0));
//	imshow("image", img2);
//}
//
//int main(int, char**)
//{
//	VideoCapture cap(0); // open the default camera
//	cap.set(CAP_PROP_FRAME_HEIGHT, 1922);
//	cap.set(CAP_PROP_FRAME_WIDTH, 2592);
//	if (!cap.isOpened())  // check if we succeeded
//		return -1;
//	Mat frame;
//	Mat sobel;
//	int mid = 1061;
//	namedWindow("frame", WINDOW_NORMAL);
//	namedWindow("sobel", WINDOW_NORMAL);
//	for (;;)
//	{
//		cap >> frame; // get a new frame from camera
//		//threshold(frame,frame,200,255,CV_THRESH_BINARY);
//		//Laplacian(frame,sobel,frame.depth(),1,1,0);
//		//line(frame, Point(0, mid), Point(2592, mid), Scalar(0, 255, 0), 2, 8, 0);
//		//line(frame, Point(0, mid-9), Point(2592, mid-9), Scalar(0, 0, 255), 2, 8, 0);
//		//line(frame, Point(0, mid+9), Point(2592, mid+9), Scalar(0, 0, 255), 2, 8, 0);
//		imshow("frame", frame);
//		//imshow("sobel", sobel);
//		if (waitKey(1) >= 0 && _kbhit()) {
//			char ch = getch();
//			orig = frame;
//			if (ch == 'c') {
//				imwrite("tipoff.jpg",frame);
//				
//			}
//			else if (ch == 'q') {
//				destroyAllWindows();
//				break;
//			}
//		}
//	}
//	//cout << "eiei" << endl;
//	//namedWindow("pic", WINDOW_NORMAL);
//	//setMouseCallback("pic", onMouse, 0);
//	//imshow("pic", frame);
//	//waitKey(0);
//
//	// the camera will be deinitialized automatically in VideoCapture destructor
//	return 0;
//}