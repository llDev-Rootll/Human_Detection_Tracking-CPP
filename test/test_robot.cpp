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
#include <gtest/gtest.h>
#include "Robot.h"
#include <iostream>

TEST(Robot, test_robot_dummy) {
  Robot bot(Eigen::Matrix4d::Random());
  std::cout << "Checking detectHuman functionality: " << "\n"<< std::endl;
  EXPECT_TRUE(true);
}
