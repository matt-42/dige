

cmake_minimum_required (VERSION 2.6)
project (sfml_window)

SET(CMAKE_VERBOSE_MAKEFILE on)

SET(SFML_ROOT ${CMAKE_SOURCE_DIR}/../../sfml2)

include_directories(${SFML_ROOT}/include)
link_directories(${SFML_ROOT}/lib)


add_executable(sfml_window main.cc)
target_link_libraries(sfml_window sfml-system sfml-window)
