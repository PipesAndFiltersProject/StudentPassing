cmake_minimum_required(VERSION 3.0)
project(appBasicInfoNode)
set(BIN_NAME BasicInfoNode) 
add_executable(${BIN_NAME} SImain.cpp)

set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS -fPIC -g -Wall)
set_target_properties(${BIN_NAME} PROPERTIES LINK_FLAGS -Wl,-lpthread)
set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 14)

# find_library(OHARBASE OHARBaseLayer NAMES libOHARBaseLayer.a REQUIRED)
# find_library(OHARSTUDENT OHARStudentLayer NAMES libOHARStudentlayer.a REQUIRED)

find_package(OHARBaseLayer CONFIG REQUIRED)
if (OHARBaseLayer_FOUND)
   message(STATUS "Base layer found")
endif()

find_package(OHARStudentLayer CONFIG REQUIRED)
if (OHARStudentLayer_FOUND)
   message(STATUS "Student layer found")
endif()

# target_link_libraries(${PROJECT_NAME} ${OHARBASE} ${OHARSTUDENT})
include_directories(${OHARBaseLayer_INCLUDE_DIR} ${OHARStudentLayer_INCLUDE_DIR})
target_link_libraries(${BIN_NAME} ${OHARBaseLayer_LIBRARIES} ${OHARStudentLayer_LIBRARIES})

target_include_directories(${BIN_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)