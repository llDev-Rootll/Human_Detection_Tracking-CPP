set(GTEST_SHUFFLE 1)

add_executable(cpp-test main.cpp HumanDetector_test.cpp Robot_test.cpp)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest PUBLIC detector_lib ${OpenCV_LIBS} ${EIGEN3_LIBS})
