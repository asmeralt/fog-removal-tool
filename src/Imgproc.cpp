#include "Imgproc.h"

#include <opencv2/imgproc.hpp>

void calcHistColored(const cv::Mat& in, cv::Mat& out, const cv::Mat& mask) {
		int histSize[] = {256, 256, 256};
		float bRanges[] = {0, 256};
		float gRanges[] = {0, 256};
		float rRanges[] = {0, 256};
		const float* ranges[] = {bRanges, gRanges, rRanges};
		int channels[] = {0, 1, 2};
	    cv::calcHist(&in, 1, channels, cv::Mat(),
	             out, 1, histSize, ranges,
	             true, true);
}

void equalizeHistColored(const cv::Mat& in, cv::Mat& out, const cv::Mat& mask) {
	cv::Mat hist;
	calcHistColored(in, hist, mask);

	hist /= in.cols * in.rows;
	hist *= 255;
	cv::Mat histHat = cv::Mat::zeros(hist.size(), hist.type());
	float* histData = (float*)hist.data;
	float* histHatData = (float*)histHat.data;
	cv::Scalar total(0, 0, 0);
	for (int i = 0; i < hist.rows; ++i) {
		for (int j = 0; j < hist.channels(); ++j) {
			total[j] += histData[i * hist.channels() + j];
			histHatData[i * hist.channels() + j] = total[j];
		}
	}
	histHat.convertTo(histHat, CV_8UC3);
	cv::LUT(in, histHat.t(), out);
	if (!mask.empty())
		in.copyTo(out, ~mask);
}
