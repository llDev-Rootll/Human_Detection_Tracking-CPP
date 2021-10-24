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
 * @file main.cpp
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
#include <fstream>
#include <iostream>

const char* path_to_model_congfiguration = "../network/yolov3.cfg";
const char* path_to_model_weights = "../network/yolov3.weights";
const char* str = "../assets/test.jpeg";  // Lena image
Mat frame = cv::imread(str);


TEST(Robot, load_network) {
  Robot test_bot(Eigen::Matrix4d::Identity());

  std::cout << "Checking load_network functionality: "<< std::endl;
  ASSERT_NO_THROW(test_bot.loadNetwork(path_to_model_congfiguration,
    path_to_model_weights));
}

TEST(Robot, test_robot_prepframe) {
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking prepframe functionality: "<< std::endl;
  Mat blob = test_bot.prepFrame(frame);  // Check size of returned
  EXPECT_EQ(1, blob.size[0]);
  EXPECT_EQ(3, blob.size[1]);
  EXPECT_EQ(416, blob.size[2]);
  EXPECT_EQ(416, blob.size[3]);
}