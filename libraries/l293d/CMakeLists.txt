add_library(l293d l293d.h)

target_link_libraries(l293d pico_stdlib)
target_include_directories(l293d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
