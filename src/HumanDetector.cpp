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
 * @file HumanDetector.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 *         Iteration 2 : Arunava Basu (Navigator) , Aditi Ramadwar (Driver)
 * @brief Class for Detecting humans and getting required data
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HumanDetector.h"

// Define static variables
int HumanDetector::human_detection_label = 0;

/**
 * @brief Construct a new Human Detector:: Human Detector object
 *        Set the thresholds for detection
 * 
 * @param conf_th : Confidence threshold value
 * @param nms_th : NMS threshold value
 */
HumanDetector::HumanDetector(float conf_th, float nms_th) {
    setConfidenceThresholds(conf_th);
    setNmsThresholds(nms_th);
}

/**
 * @brief Set confidence threshold for detection of humans
 * 
 * @param conf_th : The value of confidence threshold
 */
void HumanDetector::setConfidenceThresholds(double conf_th) {
    ModelThresholds threshold;
    confidence_threshold = conf_th;
    if (confidence_threshold < 0) {
        string arg = "confidence_threshold cannot be less than 0";
        throw std::invalid_argument(arg);
    }
}

/**
 * @brief Read the confidence threshold set in the API
 * 
 * @return double : Confidence threshold
 */
double HumanDetector::getConfidenceThresholds() {
    ModelThresholds threshold;
    return confidence_threshold;
}

/**
 * @brief Set Non-maximum suppression threshold for detection of humans
 * 
 * @param nms_th : The value of Non-maximum suppression threshold
 */
void HumanDetector::setNmsThresholds(double nms_th) {
    ModelThresholds threshold;
    nms_threshold = nms_th;
    if (nms_threshold < 0) {
        throw std::invalid_argument("nms_threshold cannot be less than 0");
    }
}

/**
 * @brief Read the Non-maximum suppression threshold set in the API
 * 
 * @return double : Non-maximum suppression threshold
 */
double HumanDetector::getNmsThresholds() {
    ModelThresholds threshold;
    return nms_threshold;
}

/**
 * @brief detection : Runs the neural network to detect humans.
 * 
 * @param net : DNN network object
 * @param blob : A 4D matrix
 * @return vector<Mat> A matrix with bounding boxes and scores
 */
vector<Mat> HumanDetector::detection(Net& net, Mat& blob) {
    net.setInput(blob);
    // Runs the forward pass to get output of the output layers
    vector<Mat> outs;
    net.forward(outs, outputsNames(net));
    return outs;
}

/**
 * @brief postProcess : Performs confidence thresholding and
 * non-max suppression.
 * 
 * @param frame : Current camera frame
 * @param outs : A matrix with bounding boxes and scores
 * @return vector<Rect> : Dimensions of the bounding 
 *                        boxes for each human detected in frame.
 */
vector<Rect> HumanDetector::postProcess(Mat& frame, const vector<Mat>& outs) {
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;
    for (size_t i = 0; i < outs.size(); ++i) {
        /* Scan through all the bounding boxes output from the network and keep only the
         * ones with high confidence scores. Assign the box's class label as the class
         * with the highest score for the box.
         */
        float* data = reinterpret_cast<float*>(outs[i].data);
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            cv::Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            // Do confidence thresholding
            if (confidence > confidence_threshold) {
                if (classIdPoint.x == 0) {
                    int centerX = static_cast<int>(data[0] * frame.cols);
                    int centerY = static_cast<int>(data[1] * frame.rows);
                    int width   = static_cast<int>(data[2] * frame.cols);
                    int height  = static_cast<int>(data[3] * frame.rows);
                    int left    = centerX - width / 2;
                    int top     = centerY - height / 2;
                    classIds.push_back(classIdPoint.x);
                    confidences.push_back(static_cast<double> (confidence));
                    boxes.push_back(Rect(left, top, width, height));
                }
            }
        }
    }
    /* Perform non maximum suppression to eliminate redundant 
     * overlapping boxes with lower confidences
     */
    vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences,
        confidence_threshold, nms_threshold, indices);
    // Draw bounding boxes and give labels
        vector<Rect> bboxes;
        bboxes.clear();
    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        Rect box = boxes[idx];
        bboxes.push_back(box);
        drawBoundingBoxes(confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame, i);
    }
    /**
     * Later, it should return the x-axis of the bounding boxes for depth
     * for transformation
     */
    return bboxes;
}

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
int HumanDetector::drawBoundingBoxes(double confidence, int left, int top,
           int right, int bottom, Mat& frame, int human_number) {
     // Draw a rectangle displaying the bounding box
    cv::rectangle(frame, cv::Point(left, top),
     cv::Point(right, bottom), cv::Scalar(0, 0, 255), 3);
    // Get the label for the class name and its confidence
    string label = cv::format("%.2f", confidence);
    label = "Human number : " +  std::to_string(human_number + 1) +
       ", Confidence : "+label;
    // Display the label and confidence at the top of the bounding box
    int baseLine;
    Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX,
     0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    cv::rectangle(frame, cv::Point(left,
     top - std::round(1.5 * labelSize.height)),
     cv::Point(left + std::round(1.5 * labelSize.width), top + baseLine),
     cv::Scalar(0, 0, 255), cv::FILLED);

    cv::putText(frame, label, cv::Point(left, top),
     cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0, 0, 0), 1);
    return 0;
}

/**
 * @brief Get the Outputs Names object
 * 
 * @param net : Network to be used for detection
 * @return vector<string> : The names of output names
 */
vector<string> HumanDetector::outputsNames(const Net& net) {
    ModelUtils utils;
    static vector<string> names;
    names = utils.getOutputsNames(net);

    return names;
}
