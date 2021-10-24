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
Eigen::Matrix4d test_matrix;
  test_matrix <<  1, 2, 0, 0,
                  4, 1, 0, 0,
                  0, 0, 1, 100,
                  0, 0, 0, 1;
    Robot bot(test_matrix);//Eigen::Matrix4d::Identity());
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
    // const char* str = "../assets/test.jpeg";  // Lena image
    // Mat frame = cv::imread(str);
        bot.detectHumans(frame, net);
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
