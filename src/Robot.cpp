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
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
 * @brief Robot class for setting parameters and calculating transformation matrix
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Robot.h"
// Define static variables
vector<int> Robot::net_input_shape = {416, 416};
double Robot::height_of_human = 171.45;

/**
 * @brief Construct a new Robot:: Robot object
 * 
 * @param transformation_matrix : The transformation matrix for
 *                                getting the location of human detected from camera's
 *                                reference frame to robot's reference frame.
 * @param f_length : Focal length of the camera being using.
 * @param p_height_of_human : Height of the human in pixel.
 */
Robot::Robot(Eigen::Matrix4d transformation_matrix,
 double f_length, double p_height_of_human) {
    transformation_cr = transformation_matrix;
    focal_length = f_length;
    pixel_height_of_human = p_height_of_human;
}

/**
 * @brief Load the pre trained network using weights and configurations
 * 
 * @param model_config : Configuration file of the model used.
 * @param model_weights : Pre trained weights of the model used.
 * @return Net : Model being used.
 */
Net Robot::loadNetwork(string model_config, string model_weights) {
    // Load the network
    Net net = cv::dnn::readNetFromDarknet(model_config,
    model_weights);
    // Define use of specific computation backend
    net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
    return net;
}

/**
 * @brief Set focal length of the camera being used.
 * 
 * @param f Focal length of the camera being used.
 */
void Robot::setFocalLength(double f) {
    focal_length = f;
}

/**
 * @brief Read the focal length defined in the API.
 * 
 * @return double The focal length set in the API.
 */
double Robot::getFocalLength() {
    return focal_length;
}

/**
 * @brief Read the size of the input used for the network
 * 
 * @return vector<int> : Size of the input used for the network
 */
vector<int> Robot::getShape() {
    return net_input_shape;
}

/**
 * @brief Set the transformation matrix for
 *        getting the location of human detected from camera's
 *        reference frame to robot's reference frame.
 * 
 * @param matrix : Transformation matrix
 */
void Robot::setTransformationMatrix(Eigen::Matrix4d matrix) {
    transformation_cr = matrix;
}

/**
 * @brief Read the transformation matrix for
 *        getting the location of human detected from camera's
 *        reference frame to robot's reference frame.
 * 
 * @return Eigen::Matrix4d : Transformation matrix
 */
Eigen::Matrix4d Robot::getTransformationMatrix() {
    return transformation_cr;
}

/**
 * @brief prepFrame : Pre processing of the camera frame
 * 
 * @param frame : Current Camera frame
 * @return Mat : processed camera frame, ready for detection
 */
Mat Robot::prepFrame(Mat frame) {
    Mat blob_frame = cv::dnn::blobFromImage(frame, 1/255.0,
     cv::Size(net_input_shape[1], net_input_shape[0]),
     cv::Scalar(0, 0, 0), true, false);
    return blob_frame;
}

/**
 * @brief Calculate the depth of the person being detected in frame
 * 
 * @param bbox_coords : The 2D coordinates of the person being detected in frame
 * @return double : the depth of the person being detected in frame
 */
double Robot::calculateDepth(Rect bbox_coords) {
    double est_depth = height_of_human * focal_length / bbox_coords.height;
    return est_depth;
}

/**
 * @brief Convert the location of human detected from camera's
 *        reference frame to robot's reference frame.
 * 
 * @param bbox_coords : location of each human in camera reference frame
 * @return vector<Rect> : location of each human in robot reference frame
 */
vector<Rect> Robot::transformToRobotFrame(vector<Rect> bbox_coords) {
    // Initialize the position vectors and variables
    Vector4d max_location      = Vector4d::Random();
    Vector4d min_location      = Vector4d::Random();
    double pix_to_cm = height_of_human/pixel_height_of_human;
    Eigen::Vector4d top_left;
    Eigen::Vector4d bottom_right;
    std::vector<Rect> final;
    final.clear();
    // Get number of detections
    int number_of_boxes = bbox_coords.size();
    // Iterate through the detection to get coordinates w.r.t robot frame
    for (int i = 0; i < number_of_boxes; i++) {
        // Create a rect for each detection
        Rect box = bbox_coords[i];
        double depth = calculateDepth(box);
        // Feed bounding box coordinates in vector of 4x1
        // Top left camera ref frame
        max_location << depth, box.x*pix_to_cm, box.y*pix_to_cm, 1;
        // Bottom right camera ref frame
        min_location << depth, box.width*pix_to_cm, box.height*pix_to_cm, 1;
        /**
         *Calculate location of point wrt robot 
         *frame using transformation matrix
         */
        top_left = transformation_cr * max_location;
        bottom_right = transformation_cr * min_location;

        // Append the position vectors in the main vector
        final.push_back(Rect(top_left[0], top_left[1],
         top_left[2], top_left[3]));
        final.push_back(Rect(top_left[0], bottom_right[1],
         bottom_right[2], bottom_right[3]));
    }
    return final;
}

/**
 * @brief Detect humans in given frame and get the location
 *        of each human in robot's reference frame
 * 
 * @param frame : Current Camera frame
 * @param net : Network for detection
 * @return vector<Rect> : Location of each human in robot's reference frame
 */
vector<Rect> Robot::detectHumans(Mat frame, Net net) {
    ModelUtils utils;
    HumanDetector hooman;
    vector<Rect> bbox;
    vector<Mat> outs;
    vector<Rect> human_locations;
    human_locations.clear();
        Mat blob = prepFrame(frame);
        // Run the detection model and get the data for detected humans
        outs = hooman.detection(utils, net, blob);
        // Apply confidence and NMS thresholding
        // Get bounding boxes dimentions and locations
        bbox = hooman.postProcess(frame, outs);
        // Testing out transformation matrix
       human_locations = transformToRobotFrame(bbox);
    return human_locations;
}
