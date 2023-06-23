add_library(c_list list.h)

target_link_libraries(c_list pico_stdlib)
target_include_directories(c_list PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
