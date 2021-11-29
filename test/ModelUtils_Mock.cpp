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
#include "Robot.h"
#include <cmath>

class MockModelUtils : public ModelUtils {
 public:
    MOCK_METHOD(vector<string>, getOutputsNames, (const Net& net));
};

/**
 * @brief Test case for getOutputNames by checking the names of the network output tensors
 * 
 */
TEST(ModelUtils, test_network_output_tensors) {
MockModelUtils model_mock
Robot test_bot(Eigen::Matrix4d::Identity());
  std::cout << "Checking network output tensors : " << std::endl;
  const char* path_to_model_congfiguration = "../network/yolov3.cfg";
  const char* path_to_model_weights = "../network/yolov3.weights";
  Net net = test_bot.loadNetwork(path_to_model_congfiguration,
    path_to_model_weights);
  static vector<string> names = model_mock.outputsNames(net);
  std::cout << names[0] << std::endl;
  EXPECT_EQ("yolo_82", names[0]);
  EXPECT_EQ("yolo_94", names[1]);
  EXPECT_EQ("yolo_106", names[2]);
}
