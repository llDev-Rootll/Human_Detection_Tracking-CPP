cmake_minimum_required(VERSION 3.2.1)
project(scratch)


# Add project cmake modules to path.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#set(OpenCV_DIR ${PROJECT_SOURCE_DIR}/cmake/)
#set path for openCV and Eigen3
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
#Add openCV 
include_directories(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

# We probably don't want this to run on every build.
option(COVERAGE "Generate Coverage Data" OFF)

if (COVERAGE)
    include(CodeCoverage)
    set(LCOV_REMOVE_EXTRA "'vendor/*'")
    setup_target_for_coverage(code_coverage test/human_detector_tracker_tests coverage)
    set(COVERAGE_SRCS src/Robot.cpp src/HumanDetector.cpp src/ModelUtils.cpp src/ModelThresholds.cpp include/Humandetector.h include/Rohot.h include/ModelUtils.h include/ModelThresholds.h )

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -g")
endif()

include(CMakeToolsHelpers OPTIONAL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(vendor/googletest/googletest)
