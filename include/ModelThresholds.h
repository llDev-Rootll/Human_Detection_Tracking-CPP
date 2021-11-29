/**
 * Copyright (c) 2021 Aditi Ramadwar
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
 * @file ModelThresholds.h
 * @brief Class for setting and getting the thresholds
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INCLUDE_MODELTHRESHOLDS_H_
#define INCLUDE_MODELTHRESHOLDS_H_
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;

/**
 * @brief A new class for the setting and getting the thresholds
 * 
 */
class ModelThresholds {
 public:
    explicit ModelThresholds(float conf_th = 0.6, float nms_th = 0.4);
   /**
     * @brief Set confidence threshold for detection of humans
     * 
     * @param conf_th : The value of confidence threshold
     */
    void setConfidenceThreshold(double conf_th);

    /**
     * @brief Read the confidence threshold set in the API
     * 
     * @return double : Confidence threshold
     */
    double getConfidenceThreshold();

    /**
     * @brief Set Non-maximum suppression threshold for detection of humans
     * 
     * @param nms_th : The value of Non-maximum suppression threshold
     */
    void setNmsThreshold(double nms_th);

    /**
     * @brief Read the Non-maximum suppression threshold set in the API
     * 
     * @return double : Non-maximum suppression threshold
     */
    double getNmsThreshold();

 private:
    double confidence_threshold;
    double nms_threshold;
};
#endif  // INCLUDE_MODELTHRESHOLDS_H_
