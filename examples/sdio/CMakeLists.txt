add_executable(sdio_example main.c)

target_link_libraries(sdio_example pico_stdio pico_sdio)

pico_add_extra_outputs(sdio_example)
