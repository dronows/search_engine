
cmake_minimum_required (VERSION 3.8)

project ("search_engine")
include (FetchContent)
FetchContent_Declare(
	googletest
    URL 
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest) 
enable_testing()

include (GoogleTest) 

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src) 
add_subdirectory(src) 
add_subdirectory(googlTest) 

configure_file(${CMAKE_SOURCE_DIR}\\resources\\config.json ${CMAKE_BINARY_DIR}\\src)   
configure_file(${CMAKE_SOURCE_DIR}\\resources\\answer.json ${CMAKE_BINARY_DIR}\\src)   
configure_file(${CMAKE_SOURCE_DIR}\\resources\\requests.json ${CMAKE_BINARY_DIR}\\src)   