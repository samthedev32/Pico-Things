add_library(pico_bluetooth bluetooth.h)

target_link_libraries(pico_bluetooth pico_stdlib hardware_uart)
target_include_directories(pico_bluetooth PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

