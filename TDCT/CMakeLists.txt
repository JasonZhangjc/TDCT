cmake_minimum_required(VERSION 2.8.9)
project(TDCT)


include_directories(include)
INCLUDE_DIRECTORIES(/usr/local/include)
add_compile_options(-std=c++11)
add_compile_options(-std=c++14)

file(GLOB SOURCES "src/*.cpp")

add_executable(TDCT ${SOURCES})
TARGET_LINK_LIBRARIES(TDCT /usr/local/lib/libbdd.so.0)


