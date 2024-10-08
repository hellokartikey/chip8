cmake_minimum_required(VERSION 3.20)

project(chip8 VERSION 0.1)

option(BUILD_TESTS "Build unit tests." ON)
option(CLANG_TIDY "Enable clang-tidy static analysis" ON)
option(CLANG_FORMAT "Enable clang-format source code formatting" ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(fetchFmt)
include(fetchRaylib)

if(BUILD_TESTS)
  include(fetchGoogletest)
endif()

include(setup)

if(CLANG_TIDY)
  include(clang_tidy)
endif()

if(CLANG_FORMAT)
  include(clang_format)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
