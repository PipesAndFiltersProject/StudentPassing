cmake_minimum_required(VERSION 3.12)
project(TestDataGenerator)
include(GNUInstallDirs)
set(APP_NAME GenerateTestData)

add_executable(${APP_NAME} main.cpp Sarge.cpp)
set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 14)
