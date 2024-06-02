cmake_minimum_required(VERSION 3.10)
project(UniqueIntervalTree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE  "Release")

##################################################################################
################################### Library ######################################
##################################################################################
file(GLOB header_files include/UniqueIntervalTree/*.hpp)

add_library(UniqueIntervalTree INTERFACE)
target_include_directories(UniqueIntervalTree INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

###################################################################################
##################################### test #######################################
###################################################################################
include(CTest)
enable_testing()
file(GLOB tests test/*.cpp)
include_directories(include/)

foreach(test ${tests})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" basetest ${test})
    add_executable(${basetest} ${test})
    add_test(${basetest} ${basetest})
endforeach()
