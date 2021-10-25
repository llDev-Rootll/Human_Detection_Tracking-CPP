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
 * @file Robot_test.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
 * @brief Run unit tests for all the methods in Robot class
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <gtest/gtest.h>
#include "Robot.h"

/**
 * @brief Test case for load network by checking if the network loads without
 * throwing an exception.
 */
TEST(Robot, load_network) {
    const char* path_to_model_congfiguration = "../network/yolov3.cfg";
    const char* path_to_model_weights = "../network/yolov3.weights";
    Robot test_bot(Eigen::Matrix4d::Identity());
    std::cout << "Checking load_network functionality: "<< std::endl;
    ASSERT_NO_THROW(test_bot.loadNetwork(path_to_model_congfiguration,
     path_to_model_weights));
}

/**
 * @brief Test case for checking prepFrame by checking the size of the returned
 * image blob
 */
TEST(Robot, test_robot_prepframe) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking prepframe functionality: " << std::endl;
  const char* str = "../assets/test.jpeg";
  Mat frame = cv::imread(str);
  Mat blob = test_bot.prepFrame(frame);
  EXPECT_EQ(1, blob.size[0]);
  EXPECT_EQ(3, blob.size[1]);
  EXPECT_EQ(416, blob.size[2]);
  EXPECT_EQ(416, blob.size[3]);
}

/**
 * @brief Test case for getShape to check network input shape 
 * 
 */
TEST(Robot, test_network_size) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking network input shape: "<< std::endl;
  EXPECT_EQ(416, test_bot.getShape()[0]);
  EXPECT_EQ(416, test_bot.getShape()[1]);
}

/**
 * @brief Test case to check setter getter for trasnformation matrix by using a test matrix
 */
TEST(Robot, test_set_transformation_matrix) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking transformation matrix setters and getters: "
   << std::endl;
  Matrix4d test_matrix;
  test_matrix <<  1, 2, 3, 0,
                  4, 5, 6, 0,
                  7, 8, 9, 0,
                  7, 8, 9, 0;
  ASSERT_NO_THROW(test_bot.setTransformationMatrix(test_matrix));
  ASSERT_EQ(test_matrix(0), test_bot.getTransformationMatrix()(0));
}

/**
 * @brief Test case for checking transformToRobotFrame method
 */
TEST(Robot, test_transformation) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking transformation to robot frame: "<< std::endl;
    vector<Rect> dummy = {Rect(0, 0, 1, 1)};
  // Run the detection model and get the data for detected humans
  ASSERT_NO_THROW(test_bot.transformToRobotFrame(dummy));
  EXPECT_EQ(1, test_bot.transformToRobotFrame(dummy).size()/2);
}

/**
 * @brief Test cases for setter getter for focal length
 */
TEST(Robot, test_focal_length) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking focal length : "<< std::endl;
  test_bot.setFocalLength(55.55);
  ASSERT_EQ(55.55, test_bot.getFocalLength());
}

/**
 * @brief Test case for checking detecthumans
 */
TEST(Robot, test_detection) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking detection functionality: "<< std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  const char* str = "../assets/test.jpeg";
  Mat frame = cv::imread(str);
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
    path_to_model_weights);
  EXPECT_EQ(2, test_bot.detectHumans(frame, net).size());
}

/**
 * @brief Test case for calculateDepth
 */
TEST(Robot, test_calculate_depth) {
  std::cout << "Checking depth calculation: "<< std::endl;
  Robot test_bot(Eigen::Matrix4d::Identity());
  Rect dummy = Rect(0, 0, 0, 672);
  EXPECT_NEAR(250.0, test_bot.calculateDepth(dummy), 5);
}
