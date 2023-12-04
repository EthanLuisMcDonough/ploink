#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include <string_view>
#include "SDL.h"
#include "ploink/game.h"

enum class GameKeyInputs : size_t {
    GAME_KEY_UP = 0,
    GAME_KEY_DOWN = 1,
    GAME_KEY_LEFT = 2,
    GAME_KEY_RIGHT = 3,
    GAME_KEY_RESET = 4,
    GAME_KEY_FINAL = 5
};

bool init_screen();
void event_loop(Game& game);
void cleanup_screen();

SDL_Window* get_window();
SDL_Renderer* get_renderer();
bool key_is_pressed(GameKeyInputs key);

SDL_FPoint get_mouse();
SDL_FPoint get_pmouse();
SDL_FPoint get_win_center();
size_t get_frame_count();
std::string_view get_exe_path();

#endif
