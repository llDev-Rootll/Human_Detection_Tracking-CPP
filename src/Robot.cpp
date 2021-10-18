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
int Robot::detectHumans() {
    HumanDetector hooman;
    // Load the network
    Net net = cv::dnn::readNetFromDarknet(path_to_model_congfiguration,
    path_to_model_weights);
    // Define use of specific computation backend
    net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
    // Start video capture by activating camera
    cv::VideoCapture cap(0);
    // Test if camera is actually active or not
    if (cap.isOpened() == false) {
      std::cout << "Cannot open the video camera" << std::endl;
      // Wait for any key press
      std::cin.get();
      return -1;
    }
    // Create name for window frame
    static const string window_name = "Human Object Detector & Tracker";
    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    // Initialize the frame that will be analysed
    Mat frame, blob;
    // Initialize variable that stores data recieved from detection model
    vector<Mat> outs;
    vector<Rect> bbox;
    // Create a loop for capturing frames in real time
    while (true) {
        // Take one frame from live feed for processing
        cap >> frame;
        // Create a pre-processed frame for detection
        blob = prepFrame(frame);
        // Run the detection model and get the data for detected humans
        outs = hooman.detection(net, blob);
        // Apply confidence and NMS thresholding
        // Get bounding boxes dimentions and locations
        bbox = hooman.postProcess(frame, outs);
        // Testing out transformation matrix
        vector<Rect> dummy = {Rect(10, 20, 30, 1)};
        transformToRobotFrame(dummy);
        // Show the frame captured on screen
        cv::imshow(window_name, frame);
        // To get continuous live video until ctrl+C is pressed
       if (cv::waitKey(1) == 27) {
           break;
       }
    }
    // Deactivate camera and close window
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
