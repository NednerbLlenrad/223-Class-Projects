cmake_minimum_required(VERSION 3.16)
project(MatchingGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

add_executable(MatchingGame Main.cpp MemoryGame.cpp)
