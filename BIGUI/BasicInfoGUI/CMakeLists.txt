cmake_minimum_required(VERSION 3.1.0)

project(BasicInfo)
set(BIN_NAME BasicInfoGUI) 

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Populate a CMake variable with the sources
set(BasicInfoGUI_SRCS
    bidialog.ui
    bidialog.cpp
    main.cpp
)

add_executable(${BIN_NAME} ${BasicInfoGUI_SRCS})

set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 14)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC TRUE)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

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

# Use the Widgets module from Qt 5
target_link_libraries(${BIN_NAME} Qt5::Widgets)

target_include_directories(${BIN_NAME} PUBLIC {Boost_INCLUDE_DIRS} ${G3LOG_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} ${G3LOG_LIBRARIES} ${Qt5Widgets_LIBRARIES} OHARBaseLayer::OHARBaseLayer OHARStudentLayer::OHARStudentLayer)
