cmake_minimum_required(VERSION 3.15)

project(checking_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(krpc)

add_executable(launch checking_systems.cpp)

# Вказуємо нашому файлу test, де шукати заголовки kRPC та згенеровані файли Protobuf
target_include_directories(launch PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/krpc/include
    ${CMAKE_CURRENT_BINARY_DIR}/krpc/protobuf/include
)
 
# Лінкуємо нашу скомпільовану бібліотеку kRPC до тестового файлу
target_link_libraries(launch PRIVATE krpc)  

target_link_options(launch PRIVATE -static -static-libgcc -static-libstdc++)