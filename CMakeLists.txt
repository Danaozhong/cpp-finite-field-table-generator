cmake_minimum_required(VERSION 3.20)

project(
  GaloisTableGenerator
  VERSION 0.1
  DESCRIPTION "A tool to generate addition/multiplication Galois tables"
  LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (GaloisTableGenerator
  src/main.cpp
  src/galois_number.h
  src/galois_number.cpp
  src/draw_tables.h
  src/draw_tables.cpp
)

target_include_directories(GaloisTableGenerator
PUBLIC
  src
)
