cmake_minimum_required(VERSION 3.8) 

add_executable (search_engine "search_engine.cpp"  "main.cpp" ${MY_INCLUDE_DIR}/search_engine.h ${MY_INCLUDE_DIR}/json_config.h) 
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

gtest_discover_tests(search_engine) 