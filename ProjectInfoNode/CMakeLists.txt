cmake_minimum_required(VERSION 3.0)
project(ProjectInfoNode)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
add_executable(${PROJECT_NAME} EWINmain.cpp)
find_library(BOOSTS boost_system REQUIRED)
find_library(OHARBASE OHARBaseLayer NAMES libOHARBaseLayer.a REQUIRED)
find_library(OHARSTUDENT OHARStudentLayer NAMES libOHARStudentlayer.a REQUIRED)
target_link_libraries(${PROJECT_NAME} ${BOOSTS} ${OHARBASE} ${OHARSTUDENT})

