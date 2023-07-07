add_executable(servo_example main.c)

target_link_libraries(servo_example pico_stdio pico_servo)

pico_add_extra_outputs(servo_example)