cmake_minimum_required(VERSION 3.25)
project(Warcraft)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warcraft main.cpp warcraft.h pos.h pos.cpp warrior.h warrior.cpp)
