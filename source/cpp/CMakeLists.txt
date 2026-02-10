cmake_minimum_required(VERSION 3.16)
project(GameOfLife VERSION 0.1.0 LANGUAGES CXX)

add_executable(GameOfLife)

target_sources(GameOfLife PRIVATE
    src/main.cpp
)
