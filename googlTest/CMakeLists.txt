cmake_minimum_required(VERSION 3.19) 

add_executable(test_search_engine "test.cpp" ${MY_SOURCE_DIR}/converterJSON.cpp
                                             ${MY_SOURCE_DIR}/invertedIndex.cpp 
                                             ${MY_SOURCE_DIR}/Search_server.cpp  ${MY_INCLUDE_DIR}) 
target_include_directories(test_search_engine PRIVATE ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR}) 
target_link_libraries(test_search_engine PRIVATE GTest::gtest_main nlohmann_json::nlohmann_json) 

include (GoogleTest) 
gtest_discover_tests(test_search_engine) 




 