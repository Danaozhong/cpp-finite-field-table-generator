cmake_minimum_required(VERSION 3.20)

project(
  GaloisTableGenerator
  VERSION 0.1
  DESCRIPTION "A tool to generate addition/multiplication Galois tables"
  LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(galois_table
  src/galois_number.h
  src/galois_number.cpp
  src/draw_tables.h
  src/draw_tables.cpp
)

target_include_directories(galois_table
PUBLIC
  src
)

add_executable (GaloisTableGenerator
  src/main.cpp
)

target_link_libraries(GaloisTableGenerator 
PRIVATE
  galois_table
)

include(CTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(galois_table_test 
  tests/test_galois_number.cpp
)

target_link_libraries(galois_table_test 
PRIVATE 
  galois_table
  GTest::gtest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(galois_table_test)