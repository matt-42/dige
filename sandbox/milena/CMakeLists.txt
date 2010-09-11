cmake_minimum_required (VERSION 2.6)
project (milena_test)

SET(CMAKE_VERBOSE_MAKEFILE on)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../.. $ENV{HOME}/olena/milena)
link_directories(${CMAKE_SOURCE_DIR}/../../build)

add_definitions(-g)
add_executable(milena_test main.cc main2.cc)
target_link_libraries(milena_test GL GLU dige ${QT_LIBRARIES})
