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
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
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
 * @brief Robot class
 */
class Robot {
 public:
    /**
     * @brief Construct a new Robot:: Robot object
     * 
     * @param transformation_matrix : The transformation matrix for
     *                                getting the location of human detected from camera's
     *                                reference frame to robot's reference frame.
     * @param f_length : Focal length of the camera being using.
     * @param p_height_of_human : Height of the human in pixel.
     */
    explicit Robot(Matrix4d transformation_matrix,
     double f_length = 984.251, double p_height_of_human = 672);

    /**
     * @brief Load the pre trained network using weights and configurations
     * 
     * @param model_config : Configuration file of the model used.
     * @param model_weights : Pre trained weights of the model used.
     * @return Net : Model being used.
     */
    Net loadNetwork(string model_config, string model_weights);

    /**
     * @brief Read the focal length defined in the API.
     * 
     * @return double The focal length set in the API.
     */
    double getFocalLength();

    /**
     * @brief Set focal length of the camera being used.
     * 
     * @param f Focal length of the camera being used.
     */
    void setFocalLength(double focal_length);

    /**
     * @brief Read the size of the input used for the network
     * 
     * @return vector<int> : Size of the input used for the network
     */
    vector<int> getShape();

    /**
     * @brief Set the transformation matrix for
     *        getting the location of human detected from camera's
     *        reference frame to robot's reference frame.
     * 
     * @param matrix : Transformation matrix
     */
    void setTransformationMatrix(Eigen::Matrix4d matrix);

    /**
     * @brief Read the transformation matrix for
     *        getting the location of human detected from camera's
     *        reference frame to robot's reference frame.
     * 
     * @return Eigen::Matrix4d : Transformation matrix
     */
    Eigen::Matrix4d getTransformationMatrix();

    /**
     * @brief prepFrame : Pre processing of the camera frame
     * 
     * @param frame : Current Camera frame
     * @return Mat : processed camera frame, ready for detection
     */
    Mat prepFrame(Mat frame);

    /**
     * @brief Calculate the depth of the person being detected in frame
     * 
     * @param bbox_coords : The 2D coordinates of the person being detected in frame
     * @return double : the depth of the person being detected in frame
     */
    double calculateDepth(Rect bbox_coords);

    /**
     * @brief Convert the location of human detected from camera's
     *        reference frame to robot's reference frame.
     * 
     * @param bbox_coords : location of each human in camera reference frame
     * @return vector<Rect> : location of each human in robot reference frame
     */
    vector<Rect> transformToRobotFrame(vector<Rect> bbox_coords);

    /**
     * @brief Detect humans in given frame and get the location
     *        of each human in robot's reference frame
     * 
     * @param frame : Current Camera frame
     * @param net : Network for detection
     * @return vector<Rect> : Location of each human in robot's reference frame
     */
    vector<Rect> detectHumans(Mat frame, Net net);

 private:
    static vector<int> net_input_shape;
    Matrix4d transformation_cr;

    double focal_length = 984.251;
    static double height_of_human;  // in cms
    double pixel_height_of_human = 672;
};
#endif  // INCLUDE_ROBOT_H_
