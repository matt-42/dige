cmake_minimum_required (VERSION 2.6)
project (ui_creation)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../..)

add_executable(ui_creation ui_creation.cc)

target_link_libraries(ui_creation ${CMAKE_SOURCE_DIR}/../../build/libdige.a
                                  ${QT_LIBRARIES})
