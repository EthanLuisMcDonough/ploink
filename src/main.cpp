#include "SDL.h"
#include "ploink/window.h"
#include "ploink/game.h"

int main(int argc, char* args[]) {
    if (!init_screen()) {
        fprintf(stderr, "Could not setup window: %s\n", SDL_GetError());
        return 1;
    }

    std::vector<Level> levels;

    DynamicCircle ball1(Vec{ 300, 160 }, 10.0f);
    DynamicCircle ball2(Vec{ 350, 150 }, 15.0f);

    std::vector<DynamicCircle> balls;
    balls.push_back(std::move(ball1));
    balls.push_back(std::move(ball2));
    

    std::vector<Bezier> bezier;
    bezier.emplace_back(100, 100, 100, 300, 300, 300);
    bezier.emplace_back(300, 300, 500, 300, 500, 250);
    bezier.emplace_back(500, 250, 500, 100, 700, 250);
    bezier.emplace_back(700, 250, 900, 400, 1200, 150);
    bezier.emplace_back(1200, 150, 1350, 50, 1200, -50);
    bezier.emplace_back(100, 100, 100, -150, 300, -150);

    levels.emplace_back(std::move(bezier), 
        std::move(balls), Vec{ 200, 100 });

    Game g(std::move(levels));
    g.init_level();

    event_loop(g);
    cleanup_screen();

    return 0;
}
