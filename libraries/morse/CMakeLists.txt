add_library(pico_morse morse.h)

target_link_libraries(pico_morse pico_stdlib hardware_gpio)

target_include_directories(pico_morse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
