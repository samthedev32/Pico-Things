add_executable(audio_example main.c)

target_link_libraries(audio_example pico_stdio pico_audio  pico_stdlib hardware_clocks hardware_pwm)

pico_add_extra_outputs(audio_example)