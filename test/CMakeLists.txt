set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    test.cpp
    src/test_Robot.cpp
    src/test_HumanDetector.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/test/include)
target_link_libraries(cpp-test PUBLIC gtest PUBLIC test_detector_lib ${OpenCV_LIBS} ${EIGEN3_LIBS})
