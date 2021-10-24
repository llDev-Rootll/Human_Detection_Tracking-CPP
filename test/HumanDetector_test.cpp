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
#include <fstream>
#include <iostream>
#include "Robot.h"




TEST(HumanDetector, test_network_output_tensors) {
HumanDetector test_hooman;
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking network output tensors : " << std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
    path_to_model_weights);
  static vector<string> names = test_hooman.getOutputsNames(net);
  EXPECT_EQ("yolo_82", names[0]);
  EXPECT_EQ("yolo_94", names[1]);
  EXPECT_EQ("yolo_106", names[2]);
}

TEST(HumanDetector, test_detection) {
  HumanDetector test_hooman;
  Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking detection functionality: "<< std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";

  const char* str = "../assets/test.jpeg"; 
  Mat frame = cv::imread(str);

  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
  path_to_model_weights);


  Mat blob = test_bot.prepFrame(frame);  // Check size of returned
  // Run the detection model and get the data for detected humans
  vector<Mat> outs;
  outs = test_hooman.detection(net, blob);
  EXPECT_EQ(3, outs.size());
  EXPECT_EQ(507, outs[0].rows);
  EXPECT_EQ(85, outs[1].cols);
}

TEST(HumanDetector, test_conf_threshold) {
HumanDetector test_hooman;
  std::cout << "Checking confidence threshold setter: "<< std::endl;
  test_hooman.setConfidenceThreshold(0.88);

  ASSERT_EQ(0.88, test_hooman.getConfidenceThreshold());
}

TEST(HumanDetector, test_nms_threshold) {
HumanDetector test_hooman;
  std::cout << "Checking nms threshold setter: "<< std::endl;
  test_hooman.setNmsThreshold(0.99);

  ASSERT_EQ(0.99, test_hooman.getNmsThreshold());
}

TEST(HumanDetector, test_invalid_thresholds) {
  std::cout << "Checking invalid theshold exception catches: "<< std::endl;
  HumanDetector invalid_thresh;
  EXPECT_THROW(invalid_thresh.setNmsThreshold(-0.99), std::invalid_argument);
  EXPECT_THROW(invalid_thresh.setConfidenceThreshold(-0.88),
   std::invalid_argument);
}
