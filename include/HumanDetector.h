#pragma once

#include<iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace std::string

class HumanDetector{
 private:
    string path_to_model_weights = "yolov3.weight";
    string path_to_model_congfiguration = "yolov3.config";
    double confidence_threshold = 0.5;
    double nms_threshold = 0.4;
 public:
    vector<cv::Mat> detection(cv::Net& net, cv::Mat& blob);
    vector<cv::Rect> postProcess(cv::Mat& frame, const vector<cv::Mat>& outs);
    int drawBoundingBoxes(int classId, double confidence, int left, int top, int right, int bottom, cv::Mat& frame);
}
