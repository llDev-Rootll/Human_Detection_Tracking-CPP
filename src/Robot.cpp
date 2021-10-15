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
Robot::Robot(Matrix4f transformation_matrix) {
	transformation_cr = transformation_matrix;
}
/**
 * @brief 
 * 
 * @param frame 
 * @param net_input_shape 
 * @return vector<cv::Mat> 
 */
Mat Robot::prepFrame(Mat frame, vector<int> net_input_shape) {
	Mat blob_frame;
	blob_frame = cv::dnn::blobFromImage(frame, 1/255.0, cv::Size(net_input_shape[1], net_input_shape[0]), cv::Scalar(0,0,0), true, false);
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
vector<double> Robot::transformToRobotFrame(Matrix4f transformation_matrix, vector<Rect> bbox_coords, double pixel_to_meter, double area_to_depth) {
	vector<double> dummy;
	return dummy;
}
/**
 * @brief 
 * 
 * @return int 
 */
int Robot::detectHumans() {
	// Load the network
	Net net = readNetFromDarknet(path_to_model_congfiguration, path_to_model_weights);
	// Define use of specific computation backend
	net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
    // Start video capture by activating camera
	cv::VideoCapture cap(0);	
	// Test if camera is actually active or not
	if (cap.isOpened() == false){ 
	  std::cout << "Cannot open the video camera" << std::endl;
	  std::cin.get(); //wait for any key press
	  return -1;
	} 
	// Create name for window frame
	static const string window_name = "Human Object Detector & Tracker";
	cv::namedWindow(window_name, cv::WINDOW_NORMAL);
	// Initialize the frame that will be analysed
	Mat frame, blob;
	// Create a loop for capturing frames in real time
	while (true) { 
		// Take one frame from live feed for processing
		cap >> frame;
		blob = prepFrame(frame, net_input_shape);
		// Show the frame captured on screen
		cv::imshow(window_name, frame);
			// To get continuous live video until ctrl+C is pressed
			if (cv::waitKey(1) == 27 ) {
				break;
			}
	}
	// Deactivate camera and close window
	cap.release();
	cv::destroyAllWindows();
	return 0;
}
