cmake_minimum_required(VERSION 3.18)

add_compile_options(-DCTEST_ENABLED)

project(pt_test)

add_executable(pt_test tests.c)
target_include_directories(pt_test PUBLIC ../include/pt .)



