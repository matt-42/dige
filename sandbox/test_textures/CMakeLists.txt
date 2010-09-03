

cmake_minimum_required (VERSION 2.6)
project (sfml_window)

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories(${CMAKE_SOURCE_DIR}/../.. $ENV{HOME}/local/include $ENV{HOME}/olena/milena)
link_directories($ENV{HOME}/local/lib)

add_executable(sfml_window main.cc)
target_link_libraries(sfml_window sfml-system sfml-window GL GLU)
