cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(QRpi)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 17)
  endif ()
endmacro(use_cxx11)

find_package(OpenCV REQUIRED)                              

set(SOURCES src/main.cpp src/lccv.cpp src/libcamera_app.cpp src/libcamera_app_options.cpp)

set(EXTRA_LIBS ${OpenCV_LIBS} libcamera-base.so libcamera.so /usr/local/lib/libzbar.so)

set(EXECUTABLE_OUTPUT_PATH "./")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wfatal-errors -Wextra -Wall -std=gnu++17 -fexceptions -ftree-vectorize -Wno-unused-parameter")

link_directories(/usr/lib/aarch64-linux-gnu/ /usr/local/lib/)

include_directories(include ${OpenCV_INCLUDE_DIRS} /usr/include/libcamera)

add_link_options(-fopenmp -s -ldl -lpthread)

add_executable(QRpi ${SOURCES})

target_link_libraries(QRpi ${EXTRA_LIBS})