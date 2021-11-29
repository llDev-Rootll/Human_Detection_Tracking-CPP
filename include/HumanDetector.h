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
#ifndef INCLUDE_HUMANDETECTOR_H_
#define INCLUDE_HUMANDETECTOR_H_
/**
 * @file HumanDetector.h
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <ModelUtils.h>
#include <ModelThresholds.h>
using std::vector;
using std::string;
using cv::Mat;
using cv::dnn::Net;
using cv::Rect;
using cv::Size;

/**
 * @brief HumanDetector Class
 * A class for human detection and drawing bounding boxes 
 */
class HumanDetector {
 public:
    /**
     * @brief Construct a new Human Detector:: Human Detector object
     *        Set the thresholds for detection
     * 
     * @param conf_th : Confidence threshold value
     * @param nms_th : NMS threshold value
     */
    explicit HumanDetector(float conf_th = 0.6, float nms_th = 0.4);

    /**
     * @brief Set confidence threshold for detection of humans
     * 
     * @param conf_th : The value of confidence threshold
     */
    void setConfidenceThresholds(double conf_th);

    /**
     * @brief Read the confidence threshold set in the API
     * 
     * @return double : Confidence threshold
     */
    double getConfidenceThresholds();

    /**
     * @brief Set Non-maximum suppression threshold for detection of humans
     * 
     * @param nms_th : The value of Non-maximum suppression threshold
     */
    void setNmsThresholds(double nms_th);

    /**
     * @brief Read the Non-maximum suppression threshold set in the API
     * 
     * @return double : Non-maximum suppression threshold
     */
    double getNmsThresholds();

    /**
     * @brief detection : Runs the neural network to detect humans.
     * 
     * @param net : DNN network object
     * @param blob : A 4D matrix
     * @return vector<Mat> A matrix with bounding boxes and scores
     */
    vector<Mat> detection(Net& net,  Mat& blob);

    /**
     * @brief postProcess : Performs confidence thresholding and
     * non-max suppression.
     * 
     * @param frame : Current camera frame
     * @param outs : A matrix with bounding boxes and scores
     * @return vector<Rect> : Dimensions of the bounding 
     *                        boxes for each human detected in frame.
     */
    vector<Rect> postProcess(Mat& frame, const vector<Mat>& outs);

    /**
     * @brief drawBoundingBoxes : Draws bouding boxes around each 
     *                            human detected in frame.
     * 
     * @param confidence : Confidence for each detection
     * @param left       : bounding box dimension
     * @param top        : bounding box dimension
     * @param right      : bounding box dimension
     * @param bottom     : bounding box dimension
     * @param frame      : Current camera frame
     * @param human_number : Number of humans detected
     * @return int : flag for indication
     */
    int drawBoundingBoxes(double confidence, int left, int top,
      int right, int bottom, Mat& frame, int human_number);

    /**
     * @brief Get the Outputs Names object
     * 
     * @param net : Network to be used for detection
     * @return vector<string> : The names of output names
     */
    vector<string> outputsNames(const Net& net);

 private:
    double confidence_threshold;
    double nms_threshold;
    static int human_detection_label;
};
#endif  // INCLUDE_HUMANDETECTOR_H_
