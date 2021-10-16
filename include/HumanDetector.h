#pragma once
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
#include <iostream>
#include <vector>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <Eigen/Dense>

using std::vector;
using std::string;
using cv::Mat;
using cv::Size;
using cv::dnn::Net;
using cv::dnn::readNetFromDarknet;
using cv::Rect;
using Eigen::Matrix4f;
using Eigen::MatrixXd;
/**
 * @brief 
 * 
 */
class HumanDetector {
 private:
    double confidence_threshold = 0.5;
    double nms_threshold = 0.4;
 public:
    vector<Mat> detection(Net& net, Mat& blob);
    vector<Rect> postProcess(Mat& frame, const vector<Mat>& outs);
    int drawBoundingBoxes(int classId, double confidence, int left, int top, int right, int bottom, Mat& frame, int human_number);
    vector<string> getOutputsNames(const Net& net);
};
