add_executable(tts_example main.c)

target_link_libraries(tts_example pico_stdio pico_tts)

pico_add_extra_outputs(tts_example)