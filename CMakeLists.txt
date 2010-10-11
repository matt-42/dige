cmake_minimum_required (VERSION 2.6)
project (dige)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories(${CMAKE_SOURCE_DIR} $ENV{HOME}/local/include)

link_directories($ENV{HOME}/local/lib)

IF(EXISTS $ENV{INSTALL_PREFIX})
  set(CMAKE_INSTALL_PREFIX $ENV{INSTALL_PREFIX} CACHE PATH "Install prefix")
ENDIF(EXISTS $ENV{INSTALL_PREFIX})

add_definitions(-D__STDC_CONSTANT_MACROS)

message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})
add_library(dige
  dige/color_picker_control.cpp
  dige/color_picker.cpp
  dige/displaylist.cpp
  dige/gl_widget.cpp
  dige/panzoom_control.cpp
  dige/panzoom.cpp
  dige/recorder.cpp
  dige/window.cpp
  dige/shortcuts/reset_panzoom.cpp
  dige/shortcuts/shortcuts.cpp)


install(TARGETS dige DESTINATION lib)
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.hpp")
