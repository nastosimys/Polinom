cmake_minimum_required(VERSION 3.24)

project(Polinom)

include(function.cmake)

add_subdirectory(mylibrary)

add_subdirectory(Polinom)

option(BTEST "build test?" OFF)

if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()

