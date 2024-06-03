cmake_minimum_required(VERSION 3.28)
project(E2 C)

set(CMAKE_C_STANDARD 23)

# Add the executable
add_executable(E2
        main.c
        src/utils/random.c
        src/utils/collision.c
        src/display.c
        src/utils/helper.h
        src/init.c
        src/utils/helper.c
        src/display.h
        src/init.h
        src/keyboard.c
        src/keyboard.h
        src/sprites.c
        src/sprites.h
        src/audio.c
        src/audio.h
        src/fx.c
        src/fx.h
        src/utils/random.h
        src/shot.c
        src/shot.h
        src/utils/collision.h
        src/ship.c
        src/ship.h
        src/alien.c
        src/alien.h
        src/global_variables.h
        src/stars.c
        src/stars.h
        src/hud.c
        src/hud.h
)

# Link the Allegro 5 libraries
target_link_libraries(E2
        liballegro.dll
        liballegro_main.dll
        liballegro_font.dll
        liballegro_ttf.dll
        liballegro_color.dll
        liballegro_image.dll
        liballegro_dialog.dll
        liballegro_video.dll
        liballegro-debug.dll
        liballegro_primitives.dll
        liballegro_audio.dll
        liballegro_acodec.dll
)

