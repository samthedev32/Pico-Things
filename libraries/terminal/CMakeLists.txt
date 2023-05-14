add_library(terminal terminal.h)

target_link_libraries(terminal pico_stdlib list)
target_include_directories(terminal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")