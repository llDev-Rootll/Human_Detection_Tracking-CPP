

# Google Mock Exercise - extra credit

## Authors

 - [Arunava Basu](https://www.linkedin.com/in/abasu713/) 
## Introduction
For this extra credit assignment, the midterm team project has been selected and the code base been refactored to include two new classes ModelUtils and ModelThresholds to implement mocks in the unit test cases. 
Since there are two team members, two separate branches, mocking a different class in each has been maintained to prevent conflict of mocks in the test cases.

## Mock Details
In the mock class, MockModelThresholds the getConfidenceThreshold function has been mocked which returns a a double value for the confidence threshold for the detection output. By mocking this function and calling the postProcess function of HumanDetector class, we have successfully isolated it from the ModelThresholds class.
## Steps to build and run tests with code coverage
Enter the following commands in the terminal:

    git clone https://github.com/llDev-Rootll/Human_Detection_Tracking-CPP/
    git checkout GMock_Extra_Credit_Arunava
    sh install_dependencies.sh // if dependencies are not installed
    sh getModels.sh
    sh build_with_coverage.sh 

    
    