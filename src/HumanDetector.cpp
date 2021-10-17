/**
 * @file HumanDetector.cpp
 * @author Iteration 1 : Aditi Ramadwar (Driver) , Arunava Basu (Navigator)
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "HumanDetector.h"
/**
 * @brief 
 * 
 * @param net 
 * @param blob 
 * @return vector<cv::Mat> 
 */
vector<Mat> HumanDetector::detection(Net& net, Mat& blob) {
	net.setInput(blob);
	// Runs the forward pass to get output of the output layers
	vector<Mat> outs;
	net.forward(outs, getOutputsNames(net));
	return outs;
}
/**
 * @brief 
 * 
 * @param frame 
 * @param outs 
 * @return vector<cv::Rect> 
 */
vector<Rect> HumanDetector::postProcess(Mat& frame, const vector<Mat>& outs) {
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;
	for (size_t i = 0; i < outs.size(); ++i) { 
		// Scan through all the bounding boxes output from the network and keep only the
		// ones with high confidence scores. Assign the box's class label as the class
		// with the highest score for the box.
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) { 
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			cv::Point classIdPoint;
			double confidence;
			// Get the value and location of the maximum score
			cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			// Do confidence thresholding
			if (confidence > confidence_threshold) { 
				if ( classIdPoint.x==0 ) { 
					int centerX = (int)(data[0] * frame.cols);
					int centerY = (int)(data[1] * frame.rows);
					int width = (int)(data[2] * frame.cols);
					int height = (int)(data[3] * frame.rows);
					int left = centerX - width / 2;
					int top = centerY - height / 2;
					classIds.push_back(classIdPoint.x);
					confidences.push_back((float)confidence);
					boxes.push_back(Rect(left, top, width, height));
				}
			}
		}
	}
	// Perform non maximum suppression to eliminate redundant overlapping boxes with
	// lower confidences
	vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, confidence_threshold, nms_threshold, indices);
	// Draw bounding boxes and give labels
	for (size_t i = 0; i < indices.size(); ++i) {
		int idx = indices[i];
		Rect box = boxes[idx];
		drawBoundingBoxes(confidences[idx], box.x, box.y,
				 box.x + box.width, box.y + box.height, frame, i);
	}
	/**
	 * Later, it should return the dimensions and coordinated (box) of the bounding boxes
	 * for transformation
	 */
	return boxes;
}

/**
 * @brief 
 * 
 * @param classId 
 * @param confidence 
 * @param left 
 * @param top 
 * @param right 
 * @param bottom 
 * @param frame 
 * @return int 
 */
int HumanDetector::drawBoundingBoxes(double confidence, int left, int top, int right, int bottom, Mat& frame, int human_number) {
	 //Draw a rectangle displaying the bounding box
	cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 178, 50), 3);
	//Get the label for the class name and its confidence
	string label = cv::format("%.2f", confidence);
	label = "Human number : " +  std::to_string(human_number+1) + ", Confidence : "+label; 
	//Display the label and confidence at the top of the bounding box
	int baseLine;
	Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
	top = cv::max(top, labelSize.height);
	cv::rectangle(frame, cv::Point(left, top - std::round(1.5*labelSize.height)), cv::Point(left + std::round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
	cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
	//std::cout << "Bounding box:" << "\n" << "Xmin: "<<left <<"\n Ymin: "<< top << "\n Xmax: " << right << "\n Ymax: " << bottom << std::endl;
	return 0;
}

/**
 * @brief 
 * 
 * @param net 
 * @return vector<string> 
 */
vector<string> HumanDetector::getOutputsNames(const Net& net) {
    static vector<string> names;
    if (names.empty()) {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();
        //get the names of all the layers in the network
        vector<string> layersNames = net.getLayerNames();
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}
