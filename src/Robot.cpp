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
/**
 * @file Robot.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Robot.h"
/**
 * @brief Construct a new Robot:: Robot object
 * 
 * @param transformation_matrix 
 */
Robot::Robot(Eigen::Matrix4d transformation_matrix) {
    transformation_cr = transformation_matrix;
}
/**
 * @brief prepFrame : Pre processing of the camera frame
 * 
 * @param frame : Current Camera frame
 * @return Mat : processed camera frame, ready for detection
 */
Net Robot::loadNetwork(string model_config, string model_weights) {
    // Load the network
    Net net = cv::dnn::readNetFromDarknet(model_config,
    model_weights);
    // Define use of specific computation backend
    net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
    return net;
}

Mat Robot::prepFrame(Mat frame) {
    Mat blob_frame;
    blob_frame = cv::dnn::blobFromImage(frame, 1/255.0,
     cv::Size(net_input_shape[1], net_input_shape[0]),
     cv::Scalar(0, 0, 0), true, false);
    return blob_frame;
}
/**
 * @brief transformToRobotFrame
 * 
 * @param bbox_coords : location of each human in camera reference frame
 * @return vector<double> : location of each human in robot reference frame
 */
vector<double> Robot::transformToRobotFrame(vector<Rect> bbox_coords) {
    // Initialize the position vectors
    Vector4d max_location      = Vector4d::Random();
    Vector4d min_location      = Vector4d::Random();
    // Get number of detections
    int number_of_boxes = bbox_coords.size();
    std::cout << "Number of boxes detected: " << number_of_boxes << std::endl;
    // Iterate through the detection to get coordinates w.r.t robot frame
    for (int i = 0; i < number_of_boxes; i++) {
        // Create a rect for each detection
        Rect box = bbox_coords[number_of_boxes];
        std::cout << box.x << box.y << box.width << box.height << std::endl;
        // Feed bounding box coordinates in vector of 4x1
        max_location << 1, box.x, box.y, 1;
        min_location << 1, box.width, box.height, 1;
        /**
         *Calculate location of point wrt robot 
         *frame using transformation matrix
         */
        Eigen::Vector4d top_left = transformation_cr * max_location;
        std::cout << "Top Left: " << top_left[0] << top_left[1] << top_left[2]
        << top_left[3] << std::endl;
        Eigen::Vector4d bottom_right = transformation_cr * min_location;
        std::cout << "Bottom Right: " << bottom_right[0] << bottom_right[1]
        << bottom_right[2] << bottom_right[3] << std::endl;
    }
    vector<double> dummy;
    return dummy;
}
/**
 * @brief detectHumans : Main method for human detection
 */
int Robot::detectHumans(Mat frame, Net net) {
    HumanDetector hooman;
    vector<Rect> bbox;
    vector<Mat> outs;
    vector<Rect> human_locations;
    bbox.clear();
    outs.clear();
    human_locations.clear();
        Mat blob = prepFrame(frame);
        // Run the detection model and get the data for detected humans
        outs = hooman.detection(net, blob);
        // Apply confidence and NMS thresholding
        // Get bounding boxes dimentions and locations
        bbox = hooman.postProcess(frame, outs);
        // Testing out transformation matrix
        vector<Rect> dummy = {Rect(10, 20, 30, 1)};
        transformToRobotFrame(dummy);

    return 0;
} 