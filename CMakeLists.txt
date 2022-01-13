cmake_minimum_required(VERSION 3.10)
project(UniqueIntervalTree)

set(CMAKE_CXX_STANDARD 20)

##################################################################################
################################### Library ######################################
##################################################################################
add_library(UniqueIntervalTree INTERFACE Include/UniqueIntervalTree/Exceptions.hpp Tests/Test1.cpp)
target_include_directories(UniqueIntervalTree INTERFACE Include/UniqueIntervalTree/)

##################################################################################
#################################### Tests #######################################
##################################################################################
include(CTest)
enable_testing()
file(GLOB tests Tests/*.cpp)
include_directories(Include/)

foreach(test ${tests})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" basetest ${test})
    add_executable(${basetest} ${test} Include/UniqueIntervalTree/Concepts.hpp Include/UniqueIntervalTree/Utils.hpp)
    add_test(${basetest} ${basetest})
endforeach()