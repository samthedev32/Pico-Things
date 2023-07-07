add_library(pico_audio audio.h)

target_link_libraries(pico_audio pico_stdlib hardware_clocks hardware_pwm)

target_include_directories(pico_audio PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
