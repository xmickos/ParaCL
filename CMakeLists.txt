cmake_minimum_required(VERSION 3.14)
project(ParaCL LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_compile_options(-Wall -Werror -O0 -g -std=c++17)

add_library(lexer src/lexer.cc src/main_definitives.hpp src/utils.cc)

add_executable(paracl src/paracl.cc src/utils.cc src/lexer.cc)

target_link_libraries(paracl PRIVATE lexer)

enable_testing()
add_subdirectory(tests)
