add_library(pico_l293d l293d.h)

target_link_libraries(pico_l293d pico_stdlib)
target_include_directories(pico_l293d PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
