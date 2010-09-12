cmake_minimum_required (VERSION 2.6)
project (dige)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories(${CMAKE_SOURCE_DIR} $ENV{HOME}/local/include)

link_directories($ENV{HOME}/local/lib)

IF(EXISTS $ENV{INSTALL_PREFIX})
  set(CMAKE_INSTALL_PREFIX $ENV{INSTALL_PREFIX})
ENDIF(EXISTS $ENV{INSTALL_PREFIX})

message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})
add_library(dige
  dige/window.cpp
  dige/recorder.cpp
  dige/shortcuts/shortcuts.cpp)


install(TARGETS dige DESTINATION lib)
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.hpp")
