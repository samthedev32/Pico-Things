add_library(stepper stepper.h)

target_link_libraries(stepper pico_stdlib)
target_include_directories(stepper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
