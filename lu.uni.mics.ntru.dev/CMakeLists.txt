cmake_minimum_required(VERSION 3.12)
project(ntrue C)

set(CMAKE_C_STANDARD 99)

add_executable(ntrue main.c sha256.c sha256.h)