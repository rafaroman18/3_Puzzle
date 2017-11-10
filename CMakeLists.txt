cmake_minimum_required(VERSION 3.8)
project(8_Puzzle)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c puzleAlum.c puzle.h nodo.h listaia.h listaia.c busquedaAlum.h busquedaAlum.c)
add_executable(8_Puzzle ${SOURCE_FILES})