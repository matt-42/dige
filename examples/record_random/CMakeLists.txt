cmake_minimum_required (VERSION 2.6)
project (record_random)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

add_executable(record_random main.cc)
target_link_libraries(record_random dige avcodec swscale ${QT_LIBRARIES})
