#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <pylon/PylonIncludes.h>


using namespace std;
using namespace Pylon;
using namespace cv;

Mat original_img;
//S.element
//for black
Mat o_kernel = getStructuringElement(MORPH_RECT, Size(1,1));
Mat c_kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
Mat ker_f_dila = getStructuringElement(MORPH_RECT, Size(5, 5));

void onMouse(int event, int x, int y, int flags, void* param)
{
	char text[100];
	Mat img2, img3;

	img2 = original_img.clone();

	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Vec3b p = img2.at<Vec3b>(y, x);
		sprintf(text, "R=%d, G=%d, B=%d", p[2], p[1], p[0]);
	}
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		cvtColor(original_img, img3, CV_BGR2HSV);
		Vec3b p = img3.at<Vec3b>(y, x);
		sprintf(text, "H=%d, S=%d, V=%d", p[0], p[1], p[2]);
	}
	else
		sprintf(text, "x=%d, y=%d", x, y);

	putText(img2, text, Point(5, 15), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0));
	imshow("image", img2);
}


Mat adjust_img(Mat original) {
	/*
	take original image to adjust
	by	1.convert to grayscale
	2.adaptive threshold
	3.close
	4.open
	5.dilation
	*/
	Mat gray_img, thres, dst, close, open, inv_open, dila;
	cvtColor(original, gray_img, CV_BGR2GRAY);

	/*namedWindow("gra", WINDOW_NORMAL);
	setMouseCallback("gra", onMouse, 0);
	imshow("gra", gray_img);*/
	adaptiveThreshold(gray_img, thres, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,57,9);
	/*threshold(gray_img, thres, t_val, 255, THRESH_BINARY);*/
	namedWindow("thres", WINDOW_NORMAL);
	imshow("thres", thres);
	imwrite("thres.jpg", thres);
	morphologyEx(thres, open, MORPH_OPEN, o_kernel);
	morphologyEx(open, close, MORPH_CLOSE, c_kernel);
	
	threshold(close, inv_open, 127, 255, THRESH_BINARY_INV);
	dilate(inv_open, dila, ker_f_dila);
	return dila;
}


int* find_2max(int arr[],int size) {
	cout << "In function find_2max" << endl;
	int *ind = new int[2];
	cout << "size : " << size << endl;
	int max_1;
	int max_2;
	
	if (arr[0] >= arr[1]) {
		cout << arr[0] << ">" << arr[1] << endl;
		max_1 = 0;
		max_2 = 1;
	}
	else {
		cout << arr[0] << "<" << arr[1] << endl;
		max_1 = 1;
		max_2 = 0;
	}
	if (size > 2) {
		for (int i = 2; i < size; i++) {
			if (arr[i] > arr[max_1]) {
				cout << arr[i] << ">" << arr[max_1] << endl;
				max_2 = max_1;
				max_1 = i;
			}
			else if (arr[i] > arr[max_2]) {
				cout << arr[i] << ">" << arr[max_2] << endl;
				max_2 = i;
			}
		}
	}

	ind[0] = max_1;
	ind[1] = max_2;
	return ind;
}

int find_index(int arr[], int val) {
	int size = sizeof(arr) / sizeof(*arr);
	for (int i = 0; i < size; i++) {
		if (arr[i] == val) return i;
	}
	return -1;
}

int* count_mat(Mat label, int n_label)
{
	int *arr = new int[n_label];
	int max_i = label.size().height;
	int max_j = label.size().width;

	for (int i = n_label - 1; i >= 0; i--)
		arr[i] = 0;

	for (int i = 0; i < max_i; i++) {
		for (int j = 0; j < max_j; j++)
		{
			arr[label.at<int>(i, j)] += 1;
		}
	}
	return arr;
}

int main() {
	original_img = imread("tipoff//tipoff2_ng.jpg");
	namedWindow("ori", WINDOW_NORMAL);
	setMouseCallback("ori", onMouse, 0);
	imshow("ori", original_img);
	waitKey(0);
	Mat dila = adjust_img(original_img);
	namedWindow("dila", WINDOW_NORMAL);
	imshow("dila", dila);
	Mat labelled, stat, centroid;
	connectedComponentsWithStats(dila, labelled, stat, centroid);
	cout <<"number of centriod"<< (centroid.size()).height << endl;
	int *area = count_mat(labelled, centroid.size().height);
	cout <<"size of each connected "<<endl;
	for (int i = 0; i < centroid.size().height; i++)
		cout << area[i] << endl;
	int *ind = find_2max(area, centroid.size().height);
	cout << ind[0] << endl;
	cout << ind[1] << endl;
	for (int i = 0; i < centroid.size().height; i++) {
		if (i != ind[0] && i != ind[1]) {
			circle(original_img, Point((int)centroid.at<double>(i, 0), (int)centroid.at<double>(i, 1)), 20, Scalar(170, 0, 255), 2, 8, 0);
		}
	}
	//if (centroid.size().height > 2){
	//	circle(original_img, Point((int)centroid.at<double>(2, 0), (int)centroid.at<double>(2, 1)), 20, Scalar(170, 0, 255), 2, 8, 0);
	//	circle(original_img, Point((int)centroid.at<double>(0, 0), (int)centroid.at<double>(0, 1)), 20, Scalar(170, 0, 255), 2, 8, 0);
	//	circle(original_img, Point((int)centroid.at<double>(1, 0), (int)centroid.at<double>(1, 1)), 20, Scalar(170, 0, 255), 2, 8, 0);
	//}
	//else {
	//	cout << "centroid has 2 centroid" << endl;
	//}
	
	namedWindow("ori_wth_cir", WINDOW_NORMAL);
	imshow("ori_wth_cir", original_img);
	waitKey(0);
	destroyAllWindows();
	//cout << sizeof(arr)<<"\n"<<sizeof(*arr)<<"\n";
	//for (int i = 4 - 1; i >= 0; i--)
		//cout << arr[i];
	return 0;
}
