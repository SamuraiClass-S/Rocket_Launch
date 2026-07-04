cmake_minimum_required(VERSION 3.15)

project(checking_system)

# 1. Задаем современный стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Ищем глобально установленный Protobuf (мы ставили его через pacman)
find_package(Protobuf REQUIRED)

# 3. Подключаем новый C++ клиент из скачанной папки
add_subdirectory("krpc/")

# 4. Создаем твой исполняемый файл
add_executable(test checking_systems.cpp)

# 5. Линкуем новый C++ клиент kRPC и сетевые библиотеки Windows
target_link_libraries(test PRIVATE
    krpc
)
