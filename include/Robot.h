#pragma once
/**
 * @file Robot.h
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
 */
class Robot {
 private:
    vector<int> net_input_shape = {416, 416};
    Matrix4f transformation_cr = Matrix4f::Random();
    string path_to_model_weights = "../network/yolov3.weights";
    string path_to_model_congfiguration = "../network/yolov3.cfg";
    double pixel_to_meter = 0;
    double area_to_depth = 0;
    Mat prepFrame(Mat frame, vector<int> net_input_shape);
    vector<double> transformToRobotFrame(Matrix4f transformation_cr, vector<Rect> bbox_coords, double pixel_to_meter, double area_to_depth);
 public:
    int detectHumans();
    Robot();
};
