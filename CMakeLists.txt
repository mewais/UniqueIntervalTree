cmake_minimum_required(VERSION 3.10)
project(UniqueIntervalTree)

set(CMAKE_CXX_STANDARD 20)

##################################################################################
################################### Library ######################################
##################################################################################
file(GLOB header_files Include/UniqueIntervalTree/*.hpp)

add_library(UniqueIntervalTree INTERFACE)
target_include_directories(UniqueIntervalTree INTERFACE Include/UniqueIntervalTree/)

###################################################################################
##################################### Test #######################################
###################################################################################
include(CTest)
enable_testing()
file(GLOB tests Test/*.cpp)
include_directories(Include/)

foreach(test ${tests})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" basetest ${test})
    add_executable(${basetest} ${test})
    add_test(${basetest} ${basetest})
endforeach()