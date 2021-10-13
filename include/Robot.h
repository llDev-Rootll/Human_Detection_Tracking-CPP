#pragma once

#include<iostream>
#include <Eigen/Dense>
#include "HumanDetector.h"

class Robot {
 private:
    vector<int> net_input_shape = [416, 416];
    Eigen::Matrix4f transformation_cr = 0;
    double pixel_to_meter = 0;
    double area_to_depth = 0;
    vector<cv::Mat> prepFrame(vector<cv::Mat> frame, vector<int> net_input_shape);
    vector<double> transformToRobotFrame(Eigen::Matrix4f transformation_matrix, vector<Rect> bbox_coords, double pixel_to_meter, double area_to_depth);
 public:
    int detectHumans();
    Robot(Eigen::Matrix4f transformation_matrix);
}
