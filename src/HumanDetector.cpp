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
	std::cout << "In HumanDetector: " << std::endl;
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
	vector<Rect> dummy;
	return dummy;
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
int HumanDetector::drawBoundingBoxes(int classId, double confidence, int left, int top, int right, int bottom, Mat& frame, int human_number) {
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
