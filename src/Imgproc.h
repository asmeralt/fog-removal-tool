#pragma once
#include <opencv2/core.hpp>

void calcHistColored(const cv::Mat& in, cv::Mat& out, const cv::Mat& mask = cv::Mat());

void equalizeHistColored(const cv::Mat& in, cv::Mat& out, const cv::Mat& mask = cv::Mat());
