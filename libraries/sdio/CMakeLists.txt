add_library(pico_sdio sdio.c)

pico_generate_pio_header(pico_sdio ${CMAKE_CURRENT_LIST_DIR}/sdio.pio)

target_link_libraries(pico_sdio pico_stdlib hardware_pio)

target_include_directories(pico_sdio PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
