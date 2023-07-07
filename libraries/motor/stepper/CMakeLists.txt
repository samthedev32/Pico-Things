add_library(pico_stepper stepper.h)

target_link_libraries(pico_stepper pico_stdlib hardware_gpio)

target_include_directories(pico_stepper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
