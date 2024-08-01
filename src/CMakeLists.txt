add_library(chip8++)

target_link_libraries(
  chip8++
  fmt::fmt
)

target_sources(
  chip8++
PRIVATE
  chip8.cpp
  parser.cpp
INTERFACE
  common.h
  chip8.h
  instructions.h
  parser.h
  stack.h
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
  chip8++
)
