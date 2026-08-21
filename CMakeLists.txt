#root
cmake_minimum_required(VERSION 3.25)
project(cona C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(libs)
add_subdirectory(engine_core)
add_subdirectory(game)
add_subdirectory(engine)
