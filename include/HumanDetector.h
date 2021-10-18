#ifndef INCLUDE_HUMANDETECTOR_H_
#define INCLUDE_HUMANDETECTOR_H_
/**
 * @file HumanDetector.h
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
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
 private:
    float confidence_threshold = 0.5;
    float nms_threshold = 0.4;
    /**
     * @brief Get the Outputs Names object
     * 
     * @param net 
     * @return vector<string> 
     */
    vector<string> getOutputsNames(const Net& net);
 public:
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
     * @param left : bounding box dimension
     * @param top  : bounding box dimension
     * @param right  : bounding box dimension
     * @param bottom  : bounding box dimension
     * @param frame  : Current camera frame
     * @param human_number : Number of humans detected
     * @return int : flag for indication
     */
    int drawBoundingBoxes(double confidence, int left, int top,
      int right, int bottom, Mat& frame, int human_number);
};
#endif  // INCLUDE_HUMANDETECTOR_H_
