
set(EXE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/executable.c")
set(LIB_SRC "${CMAKE_CURRENT_SOURCE_DIR}/library.c")

add_library(example_lib SHARED "${LIB_SRC}")
harden(example_lib)
add_sanitizers(example_lib)
target_link_libraries(example_lib PRIVATE "${PROJECT_NAME}")

add_executable(example "${EXE_SRC}")
target_link_libraries(example PRIVATE "${PROJECT_NAME}")
harden(example)
add_sanitizers(example)
