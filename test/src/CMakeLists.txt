include_directories(
    ${CMAKE_SOURCE_DIR}/test/include
)
add_library(test_detector_lib test_Robot.cpp test_HumanDetector.cpp ${CMAKE_SOURCE_DIR}/test/include/test_Robot.h ${CMAKE_SOURCE_DIR}/test/include/test_HumanDetector.h)
target_include_directories(test_detector_lib PUBLIC ../include)
