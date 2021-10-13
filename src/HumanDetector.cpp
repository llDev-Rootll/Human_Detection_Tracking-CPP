#include "HumanDetector.h"

vector<cv::Mat> HumanDetector::detection(cv::Net& net, cv::Mat& blob) {
	vector<cv::Mat> dummy;
	return dummy;
}

vector<cv::Rect> HumanDetector::postProcess(cv::Mat& frame, const vector<cv::Mat>& outs) {
	vector<cv::Rect> dummy;
	return dummy;
}

int HumanDetector:: drawBoundingBoxes(int classId, double confidence, int left, int top, int right, int bottom, cv::Mat& frame) {
	return 0;
}
