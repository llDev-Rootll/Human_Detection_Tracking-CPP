/**
 * @file main.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Robot.h"

using std::cout;
using std::endl;

int main() {
    cout << "Human Detector and Tracker" << endl;
    Robot bot(Eigen::Matrix4d::Identity());
    // Load the network
    Net net = bot.loadNetwork("../network/yolov3.cfg",
    "../network/yolov3.weights");
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
    Mat frame;
    vector<Rect> positions;
    while (true) {
        cap >> frame;
        positions = bot.detectHumans(frame, net);
        // Print positions of humans detected
        if (positions.size() > 0) {
            cout << "Number of people detected: " << positions.size()/2
            << endl;
            for (size_t i = 0; i < positions.size()/2; i++) {
                Rect upper_bound_position = positions[i*2];
                double x_u = upper_bound_position.x;
                double y_u = upper_bound_position.y;
                double z_u = upper_bound_position.width;

                Rect lower_bound_position = positions[i*2+1];
                double x_l = lower_bound_position.x;
                double y_l = lower_bound_position.y;
                double z_l = lower_bound_position.width;

                std::cout << "For person "<< i+1 << ", Postion is: (" << x_u
                 << ", "<< y_u <<", "<< z_u << ") and ("<<
                 x_l << ", "<< y_l <<", "<< z_l << ")" << std::endl;
            }
        } else {
            std::cout << "No person detected" << std::endl;
        }
        positions.clear();
        // Show the frame captured on screen
        cv::imshow(window_name, frame);
        // To get continuous live video until ctrl+C is pressed
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
