cmake_minimum_required (VERSION 2.6)
project (hello_world)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../..)

add_executable(hello_world main.cc)

target_link_libraries(hello_world ${CMAKE_SOURCE_DIR}/../../build/libdige.a
                                  ${QT_LIBRARIES})
