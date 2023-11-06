#include "SDL.h"
#include "ploink/window.h"
#include "ploink/game.h"

int main(int argc, char* args[]) {
    if (!init_screen()) {
        fprintf(stderr, "Could not setup window: %s\n", SDL_GetError());
        return 1;
    }

    std::vector<Level> levels;

    std::vector<Bezier> bezier;
    bezier.emplace_back(100, 100, 100, 300, 300, 300);

    Player p(230, 100);
    levels.emplace_back(std::move(bezier), std::move(p));

    Game g(std::move(levels));

    event_loop(g);
    cleanup_screen();

    return 0;
}
