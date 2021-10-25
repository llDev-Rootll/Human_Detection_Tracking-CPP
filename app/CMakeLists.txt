add_executable(human_detector_tracker main.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR}
)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
target_link_libraries(human_detector_tracker PUBLIC detector_lib ${OpenCV_LIBS} ${EIGEN3_LIBS})
