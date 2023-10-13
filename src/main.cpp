#include <SDL2/SDL.h>
#include "ploink/window.h"
#include "ploink/game.h"

int main(int argc, char* args[]) {
    if (!init_screen()) {
        fprintf(stderr, "Could not setup window: %s\n", SDL_GetError());
        return 1;
    }

    Game g;
    event_loop(g);
    cleanup_screen();

    return 0;
}
