cmake_minimum_required(VERSION 3.25)
project(NHF LANGUAGES C)


set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

add_executable(${PROJECT_NAME}
        src/app.c
        src/app.h
        src/aszteroida.c
        src/aszteroida.h
        src/clock.c
        src/clock.h
        src/defines.h
        src/file.c
        src/file.h
        src/font.c
        src/font.h
        src/main.c
        src/menu.c
        src/menu.h
        src/mouse.h
        src/player.c
        src/player.h
        src/ranglista.c
        src/ranglista.h
        src/reticle.c
        src/reticle.h
        src/shoot.c
        src/shoot.h)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main PRIVATE SDL2::SDL2 PRIVATE SDL2_image::SDL2_image PRIVATE SDL2_ttf::SDL2_ttf)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t ${CMAKE_BINARY_DIR} $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
)

