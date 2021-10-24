/**
 * Copyright (c) 2021 Aditi Ramadwar, Arunava Basu
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef INCLUDE_ROBOT_H_
#define INCLUDE_ROBOT_H_
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
#include <vector>
#include <string>
using Eigen::Matrix4d;
using Eigen::Vector4d;
/**
 * @brief 
 * 
 */
class Robot {
 public:
    /**
     * @brief detectHumans : Main method for human detection
     */
    int detectHumans(Mat frame, Net net);
    Net loadNetwork(string model_config, string model_weights);
    // A constructor
    explicit Robot(Matrix4d transformation_matrix);
    
 private:
    vector<int> net_input_shape = {416, 416};
    string path_to_model_weights = "../network/yolov3.weights";
    string path_to_model_congfiguration = "../network/yolov3.cfg";
    Matrix4d transformation_cr = Matrix4d::Random();
    double pixel_to_meter = 0;
    double area_to_depth = 0;
    /**
     * @brief prepFrame : Pre processing of the camera frame
     * 
     * @param frame : Current Camera frame
     * @return Mat : processed camera frame, ready for detection
     */
    Mat prepFrame(Mat frame);
    // Add double pixel_to_meter, double area_to_depth) parameters
    /**
     * @brief transformToRobotFrame
     * 
     * @param bbox_coords : location of each human in camera reference frame
     * @return vector<double> : location of each human in robot reference frame
     */
    vector<double> transformToRobotFrame(vector<Rect> bbox_coords);
};
#endif  // INCLUDE_ROBOT_H_
