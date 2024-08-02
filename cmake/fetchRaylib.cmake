include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(fetch_raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib
  GIT_TAG 5.0
  GIT_PROGRESS TRUE
  SYSTEM
)

FetchContent_MakeAvailable(fetch_raylib)
