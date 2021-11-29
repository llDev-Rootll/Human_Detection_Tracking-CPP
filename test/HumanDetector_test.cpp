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
 * @file HumanDector_test.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
 * @brief Run unit tests for all the methods in HumanDetector class
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <gtest/gtest.h>
#include <cmath>
#include "Robot.h"
#include "gmock/gmock.h"  // Brings in gMock.
using ::testing::Return; 
using ::testing::AtLeast;
using::testing::_;
class MockModelUtils : public ModelUtils {
 public:
    MOCK_METHOD1(getOutputsNames, vector<string>(int));
};

/**
 * @brief Test case for getOutputNames by checking the names of the network output tensors
 * 
 */
TEST(HumanDetector, test_network_output_tensors) {
MockModelUtils mockutils;
HumanDetector test_hooman;

Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking network output tensors : " << std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
    path_to_model_weights);
  vector<string> mock_names = {"yolo_82","yolo_94","yolo_106"};
  ON_CALL(mockutils, getOutputsNames(5))                  // #3
      .WillByDefault(Return(mock_names));

  static vector<string> names = test_hooman.outputsNames(mockutils, net);
  std::cout << names[0] << std::endl;
  EXPECT_EQ("yolo_82", names[0]);
  EXPECT_EQ("yolo_94", names[1]);
  EXPECT_EQ("yolo_106", names[2]);
}

/**
 * @brief Test case for detection method which 
 * checks the dimensions of the network output.
 */
TEST(HumanDetector, test_detection) {
  MockModelUtils mockutils;
  HumanDetector test_hooman;
  Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking detection functionality: "<< std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  const char* str = "../assets/test.jpeg";
  Mat frame = cv::imread(str);
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
  path_to_model_weights);
  Mat blob = test_bot.prepFrame(frame);
  vector<Mat> outs = test_hooman.detection(mockutils, net, blob);
  EXPECT_EQ(3, outs.size());
  EXPECT_EQ(507, outs[0].rows);
  EXPECT_EQ(85, outs[1].cols);
}

/**
 * @brief Test cases for setter and getter of confidence threshold
 */
TEST(HumanDetector, test_conf_threshold) {
ModelThresholds thresh;
  std::cout << "Checking confidence threshold setter: "<< std::endl;
  thresh.setConfidenceThreshold(0.88);

  ASSERT_EQ(0.88, thresh.getConfidenceThreshold());
}

/**
 * @brief Test cases for setter and getter of NMS threshold
 */
TEST(HumanDetector, test_nms_threshold) {
ModelThresholds thresh;
  std::cout << "Checking nms threshold setter: "<< std::endl;
  thresh.setNmsThreshold(0.99);

  ASSERT_EQ(0.99, thresh.getNmsThreshold());
}

/**
 * @brief Test cases for invalid thresholding error throw
 */
TEST(HumanDetector, test_invalid_thresholds) {
  std::cout << "Checking invalid theshold exception catches: "<< std::endl;
  ModelThresholds thresh;
  EXPECT_THROW(thresh.setNmsThreshold(-0.99), std::invalid_argument);
  EXPECT_THROW(thresh.setConfidenceThreshold(-0.88),
   std::invalid_argument);
}

/**
 * @brief Test case for checking postprocess methods by checking the number of humans detected
 */
TEST(HumanDetector, test_postprocess) {
MockModelUtils mockutils;
HumanDetector test_hooman;
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking post process functionality: "<< std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  const char* str = "../assets/test.jpeg";
  Mat frame = cv::imread(str);
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
  path_to_model_weights);
  Mat blob = test_bot.prepFrame(frame);
  vector<Mat> outs = test_hooman.detection(mockutils, net, blob);
  EXPECT_EQ(1, test_hooman.postProcess(frame, outs).size());
}
/**
 * @brief Helper function to calculate the L1 norm between two vectors
 * 
 * @param x1 x co-ordinate of first point
 * @param y1 y co-ordinate of first point
 * @param x2 x co-ordinate of second point
 * @param y2 y co-ordinate of second point
 * @return double 
 */
double euclidean_dist(double x1, double y1, double x2, double y2) {
  double x = x1 - x2;  // calculating number to square in next step
  double y = y1 - y2;
  double dist;

  dist = pow(x, 2) + pow(y, 2);       // calculating Euclidean distance
  dist = sqrt(dist);

  return dist;
}
/**
 * @brief Test case for checking the accuracy of human detection by calculating the euclidean distance between the ground truth centroids and centroids of the boxes being generated by the model.
 * 
 */
TEST(HumanDetector, test_accuracy_of_detection) {
  HumanDetector test_hooman;
  MockModelUtils mockutils;
  Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking accuracy of detection: "<< std::endl;
  double gt_h1_x = 528.0;
  double gt_h1_y = 415.5;
  double gt_h2_x = 775.5;
  double gt_h2_y = 466.5;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  const char* str = "../assets/accuracy_test.png";
  Mat frame = cv::imread(str);
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
  path_to_model_weights);
  Mat blob = test_bot.prepFrame(frame);
  vector<Mat> outs = test_hooman.detection(mockutils, net, blob);
  vector<Rect> bboxes = test_hooman.postProcess(frame, outs);
  Rect h1 = bboxes[0];
  Rect h2 = bboxes[1];
  double centroid_h1_x = h1.x + h1.width/2;
  double centroid_h1_y = h1.y + h1.height/2;
  double centroid_h2_x = h2.x + h2.width/2;
  double centroid_h2_y = h2.y + h2.height/2;
  double euclidean_distance_h1 = euclidean_dist(centroid_h1_x, centroid_h1_y,
   gt_h1_x, gt_h1_y);
  double euclidean_distance_h2 = euclidean_dist(centroid_h2_x, centroid_h2_y,
   gt_h2_x, gt_h2_y);
  EXPECT_TRUE((euclidean_distance_h2 + euclidean_distance_h1) <= 10.0);
}