# Google Mock Exercise - extra credit

## Authors
 - [Aditi Ramadwar](//www.linkedin.com/in/aditiramadwar/) 
## Introduction
For this extra credit assignment, the midterm team project has been selected and the code base been refactored to include two new classes ModelUtils and ModelThresholds to implement mocks in the unit test cases. 
Since there are two team members, two separate branches, mocking a different class in each has been maintained to prevent conflict of mocks in the test cases.

## Mock Details
In the mock class, MockModelUtils the getOutputsNames function has been mocked which returns a vector string of the output tensor names of the YOLOv3 model. By mocking this function and calling the outputsNames function of HumanDetector class, we have successfully isolated it from the ModelUtils class.
## Steps to build and run tests with code coverage
Enter the following commands in the terminal:
```
git clone https://github.com/llDev-Rootll/Human_Detection_Tracking-CPP/
git checkout GMock_Extra_Credit_Aditi
sh install_dependencies.sh // if dependencies are not installed
sh getModels.sh
sh build_with_coverage.sh
```