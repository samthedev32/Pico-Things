add_library(pico_keypad keypad.h)

target_link_libraries(pico_keypad pico_stdlib)

target_include_directories(pico_keypad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
