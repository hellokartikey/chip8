cmake_minimum_required(VERSION 3.20)

project(chip8 VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(raylib REQUIRED)
find_package(fmt REQUIRED)
find_package(magic_enum REQUIRED)
find_package(cxxopts REQUIRED)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include(GNUInstallDirs)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  find_package(GTest REQUIRED)

  include(clang_tidy)
  include(clang_format)

  enable_testing()
  add_subdirectory(tests)
endif()

add_subdirectory(src)
