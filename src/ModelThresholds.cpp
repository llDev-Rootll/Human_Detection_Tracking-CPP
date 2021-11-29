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
 * @file ModelThresholds.cpp
 * @brief Class for setting and getting the thresholds
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ModelThresholds.h"

ModelThresholds::ModelThresholds(float conf_th, float nms_th) {
    setConfidenceThreshold(conf_th);
    setNmsThreshold(nms_th);
}

void ModelThresholds::setConfidenceThreshold(double conf_th) {
    confidence_threshold = conf_th;
    if (confidence_threshold < 0) {
        string arg = "confidence_threshold cannot be less than 0";
        throw std::invalid_argument(arg);
    }
}

double ModelThresholds::getConfidenceThreshold() {
    return confidence_threshold;
}

void ModelThresholds::setNmsThreshold(double nms_th) {
    nms_threshold = nms_th;
    if (nms_threshold < 0) {
        throw std::invalid_argument("nms_threshold cannot be less than 0");
    }
}

double ModelThresholds::getNmsThreshold() {
    return nms_threshold;
}
