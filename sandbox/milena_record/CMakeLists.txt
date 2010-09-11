cmake_minimum_required (VERSION 2.6)
project (milena_test)

SET(CMAKE_VERBOSE_MAKEFILE on)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../.. $ENV{HOME}/local/include  $ENV{HOME}/olena/milena)
link_directories($ENV{HOME}/local/lib)

add_definitions(-g)
add_executable(milena_test main.cc)
target_link_libraries(milena_test ${QT_LIBRARIES} GL GLU swscale avformat avcodec dige)
