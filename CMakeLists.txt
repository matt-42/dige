cmake_minimum_required (VERSION 2.6)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_SOURCE_DIR}/cmake)

project (dige)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)

include(${QT_USE_FILE})

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories(${CMAKE_SOURCE_DIR} $ENV{HOME}/local/include)

link_directories($ENV{HOME}/local/lib)

IF(EXISTS $ENV{INSTALL_PREFIX})
  set(CMAKE_INSTALL_PREFIX $ENV{INSTALL_PREFIX} CACHE PATH "Install prefix")
ENDIF(EXISTS $ENV{INSTALL_PREFIX})
message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})


set(WITH_FFMPEG CACHE BOOL "Enable video recording (need FFmpeg)")
IF(WITH_FFMPEG)
  find_package(FFmpeg)
  if (NOT FFMPEG_FOUND)
    message(FATAL_ERROR "FFmpeg not found")
  endif (NOT FFMPEG_FOUND)
  add_definitions(-D__STDC_CONSTANT_MACROS) # Needed by ffmpeg.
  set(RECORDING_SRC dige/recorder.cpp)
  message(STATUS "Recording enabled")
ENDIF(WITH_FFMPEG)

include_directories(${FFMPEG_INCLUDE_DIR})

add_definitions(-g -W -Wall -Wextra)

add_library(dige
  dige/event/or_event.cpp
  dige/event/click.cpp
  dige/event/key_release.cpp
  dige/event/event.cpp
  dige/event/make_event.cpp
  dige/event/mouse_move.cpp
  dige/event/keycode.cpp
  dige/shortcuts/reset_panzoom.cpp
  dige/shortcuts/shortcuts.cpp
  dige/pause.cpp
  dige/widgets/gl_widget.cpp
  dige/widgets/image_view.cpp
  dige/abstract_texture.cpp
  dige/color_picker.cpp
  dige/need_qapp.cpp
  dige/window.cpp
  dige/panzoom.cpp
  dige/ui_layout.cpp
  dige/pick_coords.cpp
  dige/displaylist.cpp
  dige/color_picker_control.cpp
  dige/panzoom_control.cpp
  ${RECORDING_SRC})


install(TARGETS dige DESTINATION lib)
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.hpp")
