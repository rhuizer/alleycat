find_package(SDL)
set(SOURCES alleycat.c cat.c mt19937.c pcsound.c rand.c sound.c speaker.c
            sprites.c systemtime.c wrapper_sdl.c)
add_executable(alleycat ${SOURCES})
target_link_libraries(alleycat ${SDL_LIBRARY})
