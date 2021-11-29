set(GTEST_SHUFFLE 1)

add_executable(human_detector_tracker_tests main.cpp HumanDetector_test.cpp Robot_test.cpp)

target_include_directories(human_detector_tracker_tests PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include
                                           ../vendor/googletest/googlemock/include)
target_link_libraries(human_detector_tracker_tests PUBLIC gtest gmock PUBLIC detector_lib ${OpenCV_LIBS} ${EIGEN3_LIBS})