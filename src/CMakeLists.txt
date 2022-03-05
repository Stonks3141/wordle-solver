cmake_minimum_required(VERSION 3.5)

project(WordleSolved LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WordleSolved main.cpp)

find_package(OpenMP REQUIRED)
#target_link_libraries(WordleSolved OpenMP::OpenMP_C)
