cmake_minimum_required (VERSION 2.6)
project (milena_test)

SET(CMAKE_VERBOSE_MAKEFILE on)

include_directories(${CMAKE_SOURCE_DIR}/../.. $ENV{HOME}/local/include  /home/matt/olena/milena)
link_directories($ENV{HOME}/local/lib /usr/lib)

add_definitions(-g)
add_executable(milena_test main.cc)
target_link_libraries(milena_test sfml-system sfml-window GL GLU swscale avformat avcodec dige )
