add_library(pico_mathutil mathutil.h)

target_link_libraries(pico_mathutil pico_stdlib)

target_include_directories(pico_mathutil PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
