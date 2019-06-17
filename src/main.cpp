#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#include "Imgproc.h"

void findUnFoggedRegions(const cv::Mat& frame, cv::Mat& mask) {
	cv::cvtColor(frame, mask, cv::COLOR_BGR2GRAY);
	cv::threshold(mask, mask, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
	cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, frame.size()/60));
}

int main(int argc, char** argv) {
	if (argc < 2)
		return -1;

	cv::namedWindow("FogRemoval", cv::WINDOW_AUTOSIZE);

	cv::VideoCapture video(argv[1]);
	cv::Mat frame;
	cv::Mat mask;
	cv::Mat clearedFrame;
	cv::Mat display;
	video >> frame;
	while (true) {
		video >> frame;
		if (frame.empty() || !video.isOpened()) {
			break;
		}
		findUnFoggedRegions(frame, mask);
		equalizeHistColored(frame, clearedFrame, mask);

		cv::vconcat(frame, clearedFrame, display);
		cv::resize(display, display, cv::Size(), 0.25, 0.25);
		cv::imshow("FogRemoval", display);

		if (cv::waitKey(40) == 27)
			break;
	}
	video.release();
	return 0;
}
