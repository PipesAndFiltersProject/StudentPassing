cmake_minimum_required(VERSION 3.15.0)

project(StudentPassing VERSION 1.0.0 LANGUAGES CXX)

set(BIN_NAME spgui) 
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (WIN32)
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ("${verMajor}" MATCHES "10")
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif(CMAKE_SYSTEM_VERSION)
    endmacro(get_WIN32_WINNT)

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
    add_definitions(-DBOOST_UUID_RANDOM_PROVIDER_FORCE_WINCRYPT)
endif(WIN32)

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

