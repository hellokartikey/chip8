find_program(CLANG_FORMAT_EXE NAMES clang-format REQUIRED)

set(
  CLANG_FORMAT_HEADER_FILE_EXTENSIONS
  h hpp hxx hh h++ h# H HPP HXX hhc hpf inc
)

foreach(EXTENSION
    IN 
    LISTS
      CMAKE_CXX_SOURCE_FILE_EXTENSIONS
      CMAKE_C_SOURCE_FILE_EXTENSIONS
      CLANG_FORMAT_HEADER_FILE_EXTENSIONS
)
file(
  GLOB_RECURSE
  TMP_LIST
  ${PROJECT_SOURCE_DIR}/*.${EXTENSION}
)

list(APPEND CLANG_FORMAT_SOURCE_FILES ${TMP_LIST})
endforeach()

list(
  FILTER
  CLANG_FORMAT_SOURCE_FILES
  EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR}/*
)

add_custom_target(clang-format
  ALL
  COMMAND
    ${CLANG_FORMAT_EXE}
      -style=file
      -i ${CLANG_FORMAT_SOURCE_FILES}
  WORKING_DIRECTORY
    ${PROJECT_SOURCE_DIR}
  COMMENT
    "Formatting source files using clang-format..."
)