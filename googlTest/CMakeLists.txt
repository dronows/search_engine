cmake_minimum_required(VERSION 3.8) 


add_executable(test_search_engine "test.cpp" ${MY_SOURCE_DIR}/search_engine.cpp ) 
target_include_directories(test_search_engine PUBLIC ${MY_INCLUDE_DIR} ${MY_SOURCE_DIR}) 


target_link_libraries(test_search_engine PRIVATE GTest::gtest_main nlohmann_json::nlohmann_json) 
