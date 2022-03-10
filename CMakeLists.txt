project(GDL_Collab LANGUAGES CXX)
cmake_minimum_required(VERSION 3.22)

set(SRCS "")
file(GLOB SRCS_FOLDERS src/*)
foreach(FOLDER ${SRCS_FOLDERS})
  file(GLOB SRCS_IN_SUBFOLDER ${FOLDER}/*.cpp)
  list(APPEND SRCS ${SRCS_IN_SUBFOLDER})
endforeach()

add_subdirectory(lib/sdl2)

file(GLOB MATH_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/Math/*.cpp)
add_library(MATH_LIB ${MATH_SOURCES})
set_property(
  TARGET MATH_LIB PROPERTY INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/include
)

add_executable(GAME_EXE ${SRCS})
set_property(
  TARGET GAME_EXE PROPERTY INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/header
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/include
)
target_link_libraries(GAME_EXE SDL2 MATH_LIB)
