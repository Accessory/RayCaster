cmake_minimum_required(VERSION 3.21.0)
project(RayCaster VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)

set(CMAKE_REQUIRED_FLAGS "-fno-builtin")

add_executable(
  RayCaster
  src/globals.c
  src/map.c
  src/init_game.c
  src/draw_map.c
  src/draw_player.c
  src/utils.c
  src/draw_rays.c
  main.c)

if(MSVC)
  find_library(RAY_LIB raylib)
  target_link_libraries(${CMAKE_PROJECT_NAME} ${RAY_LIB})
else()
  target_link_libraries(${CMAKE_PROJECT_NAME} m)
  target_link_libraries(${CMAKE_PROJECT_NAME} raylib)
endif()