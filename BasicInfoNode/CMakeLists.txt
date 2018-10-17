cmake_minimum_required(VERSION 3.0)
project(appBasicInfoNode)
set(BIN_NAME BasicInfoNode) 
add_executable(${BIN_NAME} SImain.cpp)

set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS -Wall)
set_target_properties(${BIN_NAME} PROPERTIES LINK_FLAGS -Wl,-lpthread)
set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 14)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system)
find_package(g3logger REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(OHARBaseLayer REQUIRED)
if (OHARBaseLayer_FOUND)
   message(STATUS "Base layer found")
endif()

find_package(OHARStudentLayer REQUIRED)
if (OHARStudentLayer_FOUND)
   message(STATUS "Student layer found")
endif()

target_include_directories(${BIN_NAME} PUBLIC {Boost_INCLUDE_DIRS} ${g3logger_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES}  ${g3logger_LIBRARIES} OHARBaseLayer::OHARBaseLayer OHARStudentLayer::OHARStudentLayer)
