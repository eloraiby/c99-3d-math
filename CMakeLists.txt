project(3dmath)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(./3dmath SRC_LIST)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})
