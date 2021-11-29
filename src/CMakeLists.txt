include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
add_library(detector_lib Robot.cpp HumanDetector.cpp ModelUtils.cpp ModelThresholds.cpp ${CMAKE_SOURCE_DIR}/include/Robot.h ${CMAKE_SOURCE_DIR}/include/HumanDetector.h ${CMAKE_SOURCE_DIR}/include/ModelUtils.h ${CMAKE_SOURCE_DIR}/include/ModelThresholds.h)
target_include_directories(detector_lib PUBLIC ../include)