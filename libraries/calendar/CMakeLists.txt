add_library(pico_calendar calendar.h)

target_link_libraries(pico_calendar pico_stdlib)

target_include_directories(pico_calendar PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
