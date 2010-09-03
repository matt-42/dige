cmake_minimum_required (VERSION 2.6)
project (milena_test)

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories($ENV{HOME}/local/include  $ENV{HOME}/olena/milena)
link_directories($ENV{HOME}/local/lib)

add_definitions(-g)
add_executable(milena_test main.cc main2.cc)
target_link_libraries(milena_test sfml-system sfml-window GL GLU dige)
