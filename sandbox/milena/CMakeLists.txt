cmake_minimum_required (VERSION 2.6)
project (milena_test)

SET(CMAKE_VERBOSE_MAKEFILE off)

SET(SFML_ROOT ${CMAKE_SOURCE_DIR}/../../sfml2)

include_directories(${CMAKE_SOURCE_DIR}/../.. ${SFML_ROOT}/include  /home/matt/olena/milena)
link_directories(${SFML_ROOT}/lib)

add_executable(milena_test main.cc)
target_link_libraries(milena_test sfml-system sfml-window GL GLU)
