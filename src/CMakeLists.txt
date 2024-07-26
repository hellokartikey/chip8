set(BUILD_TARGET chip8)

add_library(chip8++)

target_sources(chip8++
  PRIVATE
    chip8.cpp
  PUBLIC
    common.h
    chip8.h
)

add_executable(${BUILD_TARGET})

target_sources(${BUILD_TARGET}
  PRIVATE 
    main.cpp
)

target_link_libraries(${BUILD_TARGET}
  fmt::fmt
  chip8++
)
