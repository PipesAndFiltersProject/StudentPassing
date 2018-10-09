cmake_minimum_required(VERSION 3.0)
project(appProjectInfoNode)
set(BIN_NAME ProjectInfoNode)
add_executable(${BIN_NAME} EWINmain.cpp)

set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS -Wall)
set_target_properties(${BIN_NAME} PROPERTIES LINK_FLAGS -Wl,-lpthread)
set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 11)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system)

find_package(OHARBaseLayer REQUIRED)
   if (OHARBaseLayer_FOUND)
   message(STATUS "Base layer found")
endif()

find_package(OHARStudentLayer REQUIRED)
   if (OHARStudentLayer_FOUND)
   message(STATUS "Student layer found")
endif()

target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} OHARBaseLayer::OHARBaseLayer OHARStudentLayer::OHARStudentLayer)
