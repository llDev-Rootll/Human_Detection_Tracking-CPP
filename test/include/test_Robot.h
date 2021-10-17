#ifndef TEST_INCLUDE_TEST_ROBOT_H_
#define TEST_INCLUDE_TEST_ROBOT_H_
/**
 * @file test_Robot.h
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "test_HumanDetector.h"
#include <vector>
#include <string>
using Eigen::Matrix4d;
using Eigen::Vector4d;
/**
 * @brief 
 * 
 */
class Robot {
 private:
    vector<int> net_input_shape = {416, 416};
    string path_to_model_weights = "../network/yolov3.weights";
    string path_to_model_congfiguration = "../network/yolov3.cfg";
    Matrix4d transformation_cr = Matrix4d::Random();
    Vector4d max_location      = Vector4d::Random();
    Vector4d min_location      = Vector4d::Random();
    double pixel_to_meter = 0;
    double area_to_depth = 0;
    Mat prepFrame(Mat frame);
    // Add double pixel_to_meter, double area_to_depth) parameters
    vector<double> transformToRobotFrame(vector<Rect> bbox_coords);
 public:
    int detectHumans();
    explicit Robot(Matrix4d transformation_matrix);
};
#endif  // TEST_INCLUDE_TEST_ROBOT_H_
