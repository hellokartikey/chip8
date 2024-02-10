set(BUILD_TARGET chip8)

add_executable(${BUILD_TARGET})

target_sources(
  ${BUILD_TARGET}
  PRIVATE main.cpp
  PRIVATE cpu.cpp)

target_link_libraries(
  ${BUILD_TARGET}
  fmt::fmt)

