#ifndef INCLUDE_HUMANDETECTOR_H_
#define INCLUDE_HUMANDETECTOR_H_
/**
 * @file HumanDetector.h
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using std::vector;
using std::string;
using cv::Mat;
using cv::dnn::Net;
using cv::Rect;
using cv::Size;
/**
 * @brief 
 * 
 */
class HumanDetector {
 private:
    float confidence_threshold = 0.5;
    float nms_threshold = 0.4;
    vector<string> getOutputsNames(const Net& net);
 public:
    vector<Mat> detection(Net& net,  Mat& blob);
    vector<Rect> postProcess(Mat& frame, const vector<Mat>& outs);
    int drawBoundingBoxes(double confidence, int left, int top,
      int right, int bottom, Mat& frame, int human_number);
};
#endif  // INCLUDE_HUMANDETECTOR_H_
