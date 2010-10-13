cmake_minimum_required (VERSION 2.6)
project (random)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
include(${QT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR}/../..)
add_executable(random main.cc)

IF(CMAKE_HOST_WIN32)
  set(OGL_LIB opengl32)
ENDIF(CMAKE_HOST_WIN32)

target_link_libraries(random ${CMAKE_SOURCE_DIR}/../../build/libdige.a
                             ${QT_LIBRARIES}
                             ${OGL_LIB})
