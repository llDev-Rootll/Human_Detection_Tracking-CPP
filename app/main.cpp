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
    Robot bot(Eigen::Matrix4d::Random());
    cout << "Checking detectHuman functionality: "
    << "\n" << bot.detectHumans() << endl;
    return 0;
}
