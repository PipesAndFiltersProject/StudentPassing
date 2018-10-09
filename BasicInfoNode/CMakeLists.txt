cmake_minimum_required(VERSION 3.0)
project(appBasicInfoNode)
set(BIN_NAME BasicInfoNode) 
add_executable(${BIN_NAME} SImain.cpp)

set_target_properties(${BIN_NAME} PROPERTIES COMPILE_FLAGS -Wall)
set_target_properties(${BIN_NAME} PROPERTIES LINK_FLAGS -Wl,-lpthread)
set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 11)
# set(BUILD_SHARED_LIBS FALSE)

# find_library(OHARBASE OHARBaseLayer NAMES libOHARBaseLayer.a REQUIRED)
# find_library(OHARSTUDENT OHARStudentLayer NAMES libOHARStudentlayer.a REQUIRED)

find_package(Boost 1.67.0 REQUIRED COMPONENTS system)

find_package(OHARBaseLayer REQUIRED)
if (OHARBaseLayer_FOUND)
   message(STATUS "Base layer found")
   message(STATUS ${OHARBaseLayer_LIBS})
   message(STATUS ${OHARBaseLayer_LIBRARIES})
   message(STATUS ${OHARBaseLayer_LIBRARY})
endif()

find_package(OHARStudentLayer REQUIRED)
if (OHARStudentLayer_FOUND)
   message(STATUS "Student layer found")
endif()

# target_link_libraries(${PROJECT_NAME} ${OHARBASE} ${OHARSTUDENT})
# include_directories(${OHARBaseLayer_INCLUDE_DIR} ${OHARStudentLayer_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
# target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} ${OHARBaseLayer_LIBRARIES} ${OHARStudentLayer_LIBRARIES})
target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} OHARBaseLayer::OHARBaseLayer OHARStudentLayer::OHARStudentLayer)

# target_include_directories(${BIN_NAME} PUBLIC
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
#)
