cmake_minimum_required (VERSION 2.6)
project (random)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

add_executable(random main.cc)
target_link_libraries(random dige ${QT_LIBRARIES})
