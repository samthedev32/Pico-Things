add_library(list list.h)

target_link_libraries(list pico_stdlib)
target_include_directories(list PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")