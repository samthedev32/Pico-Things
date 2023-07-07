add_library(pico_graphics graphics.h)

target_link_libraries(pico_graphics pico_stdlib pico_mathutil)
target_include_directories(pico_graphics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
