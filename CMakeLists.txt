cmake_minimum_required (VERSION 2.8)
project (event_track)
include_directories("${PROJECT_SOURCE_DIR}")

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()

add_executable(unittest unittest.cpp find_event_samples.hpp catch.hpp)
add_executable(generate_example generate_example.cpp find_event_samples.hpp)