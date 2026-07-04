cmake_minimum_required(VERSION 3.15)

project(checking_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(krpc)

add_executable(test checking_systems.cpp)

target_link_libraries(test PRIVATE krpc)