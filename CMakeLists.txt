cmake_minimum_required(VERSION 3.10)

project(checking_system)

add_subdirectory("lib/krpc-cpp-0.5.4")

add_executable(test checking_systems.cpp)

target_include_directories(test PRIVATE 
    "${CMAKE_SOURCE_DIR}/lib/asio-1.36.0/include"
)
 
find_package(Protobuf REQUIRED)

target_link_libraries(test PRIVATE
    krpc #lib mod krpc
    protobuf::libprotobuf #lib protobuf
    ws2_32 #sys lib windows for network (need for ASIO)
    mswsock #sys lib windows for network

)  