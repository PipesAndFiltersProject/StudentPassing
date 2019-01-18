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

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

add_executable(${BIN_NAME} ${BasicInfoGUI_SRCS})

set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${BIN_NAME} PROPERTIES LINK_FLAGS -pthread)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

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

target_include_directories(${BIN_NAME} PUBLIC {Boost_INCLUDE_DIRS} ${G3LOG_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} ${G3LOG_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} OHARBaseLayer::OHARBaseLayer OHARStudentLayer::OHARStudentLayer)
