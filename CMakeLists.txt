project(3dmath C)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "--std=c99 ${CMAKE_C_FLAGS}")
    endif ()
else ()
    set (CMAKE_C_STANDARD 99)
endif ()

set(HEADER_FILES 3dmath.h)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${HEADER_FILES})
add_library(${PROJECT_NAME}s STATIC ${SRC_LIST} ${HEADER_FILES})
