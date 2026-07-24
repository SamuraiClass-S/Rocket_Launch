cmake_minimum_required(VERSION 3.15) # Оновлюємо базову версію, бо kRPC 0.6.0 вимагає мінімум 3.15

project(checking_system)

# 2. Підключаємо нову папку
add_subdirectory("libs/krpc")

# 3. Наш головний файл
add_executable(test checking_systems.cpp)

# 4. Лінкуємо все разом. 
# Зверни увагу: kRPC тепер сам передасть нам шляхи до ASIO і Protobuf, 
# тому нам більше не треба писати target_include_directories та find_package!
target_link_libraries(test PRIVATE
    krpc                     
    ws2_32                   
    mswsock                  
)