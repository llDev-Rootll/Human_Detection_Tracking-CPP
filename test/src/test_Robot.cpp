/**
 * @file test_robot.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "test_Robot.h"
/**
 * @brief Construct a new Robot:: Robot object
 * 
 * @param transformation_matrix 
 */
Robot::Robot(Eigen::Matrix4d transformation_matrix) {
    transformation_cr = transformation_matrix;
}
/**
 * @brief 
 * 
 * @param frame 
 * @param net_input_shape 
 * @return vector<cv::Mat> 
 */
Mat Robot::prepFrame(Mat frame) {
    Mat blob_frame;
    blob_frame = cv::dnn::blobFromImage(frame, 1/255.0,
     cv::Size(net_input_shape[1], net_input_shape[0]),
     cv::Scalar(0, 0, 0), true, false);
    return blob_frame;
}
/**
 * @brief
 * 
 * @param transformation_matrix 
 * @param bbox_coords 
 * @param pixel_to_meter
 * @param area_to_depth 
 * @return vector<double> 
 */
vector<double> Robot::transformToRobotFrame(vector<Rect> bbox_coords) {
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
 * @brief 
 * 
 * @return int 
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