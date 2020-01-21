cmake_minimum_required(VERSION 3.15.0)

project(StudentPassing VERSION 1.0.0 LANGUAGES CXX)

set(BIN_NAME spgui) 
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# IF(APPLE)
#     # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
#     LINK_DIRECTORIES(/usr/local/lib)
# ENDIF()

# Populate a CMake variable with the sources
set(StudentPassingGUI_SRCS
    bidialog.ui
    bidialog.h
    bidialog.cpp
    main.cpp
)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

add_executable(${BIN_NAME} ${StudentPassingGUI_SRCS})

set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${BIN_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ProcessorNode REQUIRED)
find_package(StudentNodeElements REQUIRED)

find_package(Boost 1.70.0 COMPONENTS system REQUIRED)
find_package(g3logger REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Find the Qt libraries
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

target_include_directories(${BIN_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${G3LOG_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${ProcessorNode_INCLUDE_DIRS} ${StudentNodeElements_INCLUDE_DIRS})

target_link_libraries(${BIN_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Boost::system g3logger StudentNodeElements::StudentNodeElements ProcessorNode::ProcessorNode)

