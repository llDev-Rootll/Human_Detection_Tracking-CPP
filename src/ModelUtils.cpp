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
 * @file ModelUtils.cpp
 * @author Aditi Ramadwar
 * @brief Class for uploading the model information
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "ModelUtils.h"

/**
 * @brief Get the Outputs Names object
 * 
 * @param net : Network to be used for detection
 * @return vector<string> : The names of output names
 */
vector<string> ModelUtils::getOutputsNames(const Net& net) {
    static vector<string> names;
    if (names.empty()) {
        // Get the indices of the output layers, i.e. the layers
        // with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();
        // Get the names of all the layers in the network
        vector<string> layersNames = net.getLayerNames();
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}
