add_executable(test_chip8)

target_sources(
  test_chip8
PRIVATE
  fixture.h
  registerapi.cpp
  memoryapi.cpp
  parser.cpp
  stack.cpp
  opcode.cpp
)

target_include_directories(
  test_chip8
PRIVATE
  ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(
  test_chip8
  GTest::gtest_main
  chip8++
)

include(GoogleTest)
gtest_discover_tests(test_chip8)
