add_library(chip8++)

target_link_libraries(
  chip8++
  fmt::fmt
  magic_enum::magic_enum
  raylib
)

target_sources(
  chip8++
PRIVATE
  chip8.cpp
  parser.cpp
  screen.cpp
  keyboard.cpp
INTERFACE
  common.h
  chip8.h
  instructions.h
  parser.h
  stack.h
  screen.h
  bit.h
  keyboard.h
  helpers.h
  timer.h
)

add_executable(chip8)

target_sources(
  chip8
PRIVATE
  main.cpp
)

target_link_libraries(
  chip8
  fmt::fmt
  cxxopts::cxxopts
  chip8++
)

install(TARGETS chip8)
