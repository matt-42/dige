cmake_minimum_required (VERSION 2.6)
project (record_random)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../.. $ENV{HOME}/olena/milena)

add_executable(record_random main.cc)

IF(CMAKE_HOST_WIN32)
  set(OGL_LIB opengl32 glu32)
ENDIF(CMAKE_HOST_WIN32)

target_link_libraries(record_random ${CMAKE_SOURCE_DIR}/../../build/libdige.a
  avcodec
  swscale
  avformat
  ${OGL_LIB}
  ${QT_LIBRARIES})
