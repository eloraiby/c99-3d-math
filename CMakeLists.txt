project(3dmath C)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(3dmath SRC_LIST)
set(HEADER_FILES 3dmath/mathlib.h)
add_definitions(-DBUILDING_3DMATH_DLL)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} ${HEADER_FILES})
add_library(${PROJECT_NAME}s STATIC ${SRC_LIST} ${HEADER_FILES})

