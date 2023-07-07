add_library(pico_tts tts.h)

target_link_libraries(pico_tts pico_stdlib pico_audio)

target_include_directories(pico_tts PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")