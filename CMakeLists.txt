cmake_minimum_required(VERSION 3.5)
project(optimization_demo)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/")

find_package(Glog REQUIRED)

include_directories(
    ${GLOG_INCLUDE_DIR}
)

add_executable(optimization_demo main.cpp time_recorder.cpp)

target_link_libraries(optimization_demo
    ${GLOG_LIBRARIES}
)