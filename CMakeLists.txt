cmake_minimum_required(VERSION 3.14)
project(ParaCL LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_library(lexer_lib src/lexer.cc src/main_definitives.hpp)

add_executable(paracl src/paracl.cc src/utils.cc src/lexer.cc)

target_compile_options(paracl PUBLIC -Wall -Werror -O0 -g -std=c++17)

target_link_libraries(paracl PRIVATE lexer_lib)

enable_testing()
add_subdirectory(tests)
