add_library(c_terminal terminal.h)

target_link_libraries(c_terminal pico_stdlib c_list)
target_include_directories(c_terminal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
