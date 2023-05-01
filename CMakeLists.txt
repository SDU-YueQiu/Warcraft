cmake_minimum_required(VERSION 3.25)
project(Warcraft)

set(CMAKE_CXX_STANDARD 17)

add_executable(Warcraft main.cpp pos.cpp pos.h warcraft.cpp warcraft.h warrior.h warrior.cpp)
