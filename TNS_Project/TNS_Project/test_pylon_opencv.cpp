//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <Windows.h>
//#include <conio.h>
//#include <pylon/PylonIncludes.h>
//#ifdef PYLON_WIN_BUILD
//#	include <pylon/PylonGUI.h>
//#endif
//#define saveImages 1
//#define recordVideo 0
//using namespace std;
//using namespace Pylon;
//using namespace cv;
//static const uint32_t c_countOfImagesToGrab = 100;
//int main() {
//	Pylon::PylonAutoInitTerm autoInitTerm;
//	try
//	{
//		CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
//		cout << "Using device" << camera.GetDeviceInfo().GetModelName() << endl;
//		GenApi::INodeMap& nodemap = camera.GetNodeMap();
//		camera.Open();
//		GenApi::CIntegerPtr width = nodemap.GetNode("Width");
//		GenApi::CIntegerPtr height = nodemap.GetNode("Height");
//		camera.MaxNumBuffer = 5;
//		CImageFormatConverter formatConverter;
//		formatConverter.OutputPixelFormat = PixelType_BGR8packed;
//		CPylonImage pylonImage;
//		int grabbedImages = 5;
//		Mat openCvImage;
//		camera.StartGrabbing();
//		CGrabResultPtr ptrGrabResult;
//		while (camera.IsGrabbing()) {
//			camera.RetrieveResult(1000, ptrGrabResult, TimeoutHandling_ThrowException);
//			if (ptrGrabResult->GrabSucceeded()) {
//			/*	cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
//				cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;*/
//				formatConverter.Convert(pylonImage, ptrGrabResult);
//				openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)pylonImage.GetBuffer());
//				/*if (saveImages) {
//					std::ostringstream s;
//					s << "image_" << grabbedImages << ".jpg";
//					string imageName(s.str());
//					imwrite(imageName, openCvImage);
//					grabbedImages++;
//				}*/
//				
//				namedWindow("OpenCV_Display_window", CV_WINDOW_NORMAL);
//				imshow("OpenCV_Display_window", openCvImage);
//				if (_kbhit()/*check if high-order bit is set (1 << 15)*/)
//				{	
//					char ch = getch();
//					if (ch =='c') {
//						cout << "capture" << grabbedImages << endl;
//						std::ostringstream s;
//						s << "image_" << grabbedImages << ".jpg";
//						string imageName(s.str());
//						imwrite(imageName, openCvImage);
//						grabbedImages++;
//					}
//					else if (ch == 'q') {
//						cout << "quit" << endl;
//						return 0;
//					}
//				}
//				waitKey(5);
//			}
//		}
//	}
//	catch (const std::exception&)
//	{
//		cout << "error" << endl;
//	}
//
//
//	return 0;
//}
//
