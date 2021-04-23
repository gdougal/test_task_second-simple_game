cmake_minimum_required(VERSION 3.17)
project(hello_sfml)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_NAME "hello_sfml")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Frameworks)
add_executable(${EXECUTABLE_NAME} srcs/main.cpp srcs/classes/canonball_t.cpp srcs/classes/canonball_t.hpp srcs/classes/scope_t.cpp srcs/classes/scope_t.hpp srcs/shooting_range.hpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/.)

link_directories(${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${EXECUTABLE_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-audio.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-graphics.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-network.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-system.dylib
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsfml-window.dylib
        )

