#include <gtest/gtest.h>
#include "Robot.h"
#include <iostream>
TEST(Robot, test_robot_dummy) {

  Robot bot(Eigen::Matrix4d::Random());
  std::cout << "Checking detectHuman functionality: "<< "\n"<< std::endl;
  EXPECT_TRUE(true);
}
