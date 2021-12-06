cmake_minimum_required(VERSION 3.21)
project(DSCAP)

set(CMAKE_CXX_STANDARD 20)

add_executable(DSCAP Main.cpp src/Lexer.cpp  src/Parser.cpp)
