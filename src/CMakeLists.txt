add_library(chip8++)

target_sources(
  chip8++
PRIVATE
  chip8.cpp
INTERFACE
  common.h
  chip8.h
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
