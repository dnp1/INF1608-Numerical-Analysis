cmake_minimum_required(VERSION 3.3)
project(inf1608_numerical_analysis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

aux_source_directory(./modules LIB_DIRS)

add_executable(inf1608_numerical_analysis main.cpp ${LIB_DIRS})

add_custom_command(TARGET inf1608_numerical_analysis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:inf1608_numerical_analysis>/resources)