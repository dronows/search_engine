cmake_minimum_required(VERSION 3.19) 
add_executable (search_engine  "main.cpp" "converterJSON.cpp" "invertedIndex.cpp" "Search_server.cpp" ${MY_INCLUDE_DIR}  ) 
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/docs $<TARGET_FILE_DIR:${PROJECT_NAME}>/docs)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)