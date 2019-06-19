cmake_minimum_required(VERSION 3.14)
project(tinder C)

set(CMAKE_C_STANDARD 99)

add_executable(tinder grafo.c leitor.c main.c)