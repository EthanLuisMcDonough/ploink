#include <iostream>
#include "SDL.h"
#include "ploink/window.h"
#include "ploink/game.h"
#include "ploink/loader.h"

int main(int argc, char* args[]) {
    if (!init_screen()) {
        fprintf(stderr, "Could not setup window: %s\n", SDL_GetError());
        return 1;
    }

    std::vector<Level> levels = load_levels();

    Game g(std::move(levels));
    g.init_level();

    event_loop(g);
    cleanup_screen();

    return 0;
}
