cmake_minimum_required (VERSION 2.6)
project (simple_image)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../..)

add_executable(simple_image main.cc)

IF(CMAKE_HOST_WIN32)
  set(OGL_LIB opengl32 glu32)
ENDIF(CMAKE_HOST_WIN32)

target_link_libraries(simple_image ${CMAKE_SOURCE_DIR}/../../build/libdige.a
  ${OGL_LIB}
  ${QT_LIBRARIES})
