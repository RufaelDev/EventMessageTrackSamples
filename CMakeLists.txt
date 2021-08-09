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

add_executable(unittest unittest.cpp event_track.cpp fmp4stream.cpp catch.hpp base64.cpp event_track.h fmp4stream.h)
add_executable(generate_example generate_example.cpp event_track.cpp fmp4stream.cpp base64.cpp event_track.h fmp4stream.h)
add_executable(fmp4DashEvent fmp4DashEvent.cpp event_track.cpp fmp4stream.cpp base64.cpp event_track.h fmp4stream.h)
add_executable(dashEventfmp4 dashEventfmp4.cpp event_track.cpp fmp4stream.cpp base64.cpp tinyXML2.cpp event_track.h fmp4stream.h)