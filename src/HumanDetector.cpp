/**
 * @file HumanDetector.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HumanDetector.h"
/**
 * @brief 
 * 
 * @param net 
 * @param blob 
 * @return vector<cv::Mat> 
 */
vector<cv::Mat> HumanDetector::detection(cv::Net& net, cv::Mat& blob) {
	vector<cv::Mat> dummy;
	return dummy;
}
/**
 * @brief 
 * 
 * @param frame 
 * @param outs 
 * @return vector<cv::Rect> 
 */
vector<cv::Rect> HumanDetector::postProcess(cv::Mat& frame, const vector<cv::Mat>& outs) {
	vector<cv::Rect> dummy;
	return dummy;
}
/**
 * @brief 
 * 
 * @param classId 
 * @param confidence 
 * @param left 
 * @param top 
 * @param right 
 * @param bottom 
 * @param frame 
 * @return int 
 */
int HumanDetector:: drawBoundingBoxes(int classId, double confidence, int left, int top, int right, int bottom, cv::Mat& frame) {
	return 0;
}
