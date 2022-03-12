project(GDL_Collab LANGUAGES CXX)
cmake_minimum_required(VERSION 3.14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

file(GLOB SRCS_FOLDERS src/*)
foreach(FOLDER ${SRCS_FOLDERS})
  file(GLOB SRCS_IN_SUBFOLDER ${FOLDER}/*.cpp)
  list(APPEND SRCS ${SRCS_IN_SUBFOLDER})
endforeach()

# todo: Make its release type independent, possibly by invoking new cmake process
#       Otherwise it would be necessary to recompile SDL each time build type changes
# todo: Copy shared objects from sdl2 folder to executable
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
set_property(
  TARGET GAME_EXE PROPERTY RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(GAME_EXE SDL2 MATH_LIB)

if(MINGW)
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(GAME_EXE PRIVATE -g3 -ggdb)
  endif()
  target_link_libraries(GAME_EXE -lmingw32)
endif()

if(MSVC)
  target_compile_options(GAME_EXE PRIVATE /W4 /WX)
else()
  target_compile_options(GAME_EXE PRIVATE -Wall -Wextra -Wpedantic)
endif()
