add_executable(slcd_example main.c)

target_link_libraries(slcd_example pico_stdio pico_slcd)

pico_add_extra_outputs(slcd_example)