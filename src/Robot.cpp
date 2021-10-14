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
Robot::Robot() {
	
}
/**
 * @brief 
 * 
 * @param frame 
 * @param net_input_shape 
 * @return vector<cv::Mat> 
 */
Mat Robot::prepFrame(Mat frame, vector<int> net_input_shape) {
	Mat dummy;
	return dummy;
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
	return 0;
}
