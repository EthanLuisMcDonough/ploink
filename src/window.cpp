#include "ploink/window.h"
#include "ploink/game.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool keys[static_cast<size_t>(GameKeyInputs::GAME_KEY_FINAL)];

float mouse_x = 0, mouse_y = 0,
    pmouse_x = 0, pmouse_y = 0;

bool init_screen() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    window = SDL_CreateWindow(
        "ploink",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        700, 700, SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        return false;
    }
    return true;
}

void handle_key_event(SDL_KeyboardEvent e) {
    bool is_keydown = e.type == SDL_KEYDOWN;
    switch (e.keysym.sym) {
        case SDLK_UP:
            keys[static_cast<size_t>(GameKeyInputs::GAME_KEY_UP)] = is_keydown;
            break;
        case SDLK_DOWN:
            keys[static_cast<size_t>(GameKeyInputs::GAME_KEY_DOWN)] = is_keydown;
            break;
        case SDLK_RIGHT:
            keys[static_cast<size_t>(GameKeyInputs::GAME_KEY_RIGHT)] = is_keydown;
            break;
        case SDLK_LEFT:
            keys[static_cast<size_t>(GameKeyInputs::GAME_KEY_LEFT)] = is_keydown;
            break;
    }
}

void handle_motion_event(SDL_MouseMotionEvent e) {
    pmouse_x = mouse_x;
    pmouse_y = mouse_y;
    mouse_x = e.x;
    mouse_y = e.y;
}

bool handle_event(SDL_Event e) {
    switch (e.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            handle_key_event(e.key);
            break;
        case SDL_MOUSEMOTION:
            handle_motion_event(e.motion);
            break;
        case SDL_QUIT:
            return true;
    }
    return false;
}

bool key_is_pressed(GameKeyInputs key) {
    return keys[static_cast<size_t>(key)];
}

void event_loop(Game& g) {
    long timestamp = SDL_GetTicks();
    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (handle_event(e)) {
                return;
            }
        }
        long new_timestamp = SDL_GetTicks();
        double dt = new_timestamp - timestamp;
        if (dt > 1000.0/FRAME_RATE) {
            g.update();
            g.render(renderer);
        }
    }
}

void cleanup_screen() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* get_window() {
    return window;
}

SDL_Renderer* get_renderer() {
    return renderer;
}

SDL_FPoint get_mouse() {
    return SDL_FPoint{ mouse_x, mouse_y };
}

SDL_FPoint get_pmouse() {
    return SDL_FPoint{ pmouse_x, pmouse_y };
}
