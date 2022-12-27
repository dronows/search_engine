
cmake_minimum_required (VERSION 3.19)

project ("search_engine")
set(CMAKE_CXX_STANDARD 14) 

include (FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest) 

enable_testing()
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(MY_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src) 
add_subdirectory(src) 
add_subdirectory(googlTest) 




