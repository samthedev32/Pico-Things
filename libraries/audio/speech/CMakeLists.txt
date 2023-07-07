add_library(pico_speech speech.h)

target_link_libraries(pico_speech pico_stdlib pico_mic)

target_include_directories(pico_speech PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")