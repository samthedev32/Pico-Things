add_executable(rocketbenchy main.c)

target_link_libraries(rocketbenchy pico_sd)

pico_add_extra_outputs(rocketbenchy)
