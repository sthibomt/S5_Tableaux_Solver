cmake_minimum_required(VERSION 3.10)
project(s5tableau CXX)
set(CMAKE_CXX_STANDARD 17)
add_executable(s5_tableau 
s5_tableau.cpp
Parser.h
Formula.h
)