cmake_minimum_required(VERSION 3.12)
project(ntrue C)

set(CMAKE_C_STANDARD 99)

add_executable(ntrue mgf1-test.c sha256.c sha256.h mgf1.c mgf1.h)