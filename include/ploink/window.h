#ifndef _GAME_WINDOW_H
#define _GAME_WINDOW_H

#include <string_view>
#include "SDL.h"
#include "ploink/game.h"

/// <summary>
/// Enum of different keys that can be possibly pressed
/// </summary>
enum class GameKeyInputs : size_t {
    GAME_KEY_UP = 0,
    GAME_KEY_DOWN = 1,
    GAME_KEY_LEFT = 2,
    GAME_KEY_RIGHT = 3,
    GAME_KEY_RESET = 4,
    GAME_KEY_FINAL = 5
};

/// <summary>
/// Starts SDL
/// </summary>
/// <returns>True if successful</returns>
bool init_screen();

/// <summary>
/// Runs game event loop
/// </summary>
/// <param name="game">The game to run</param>
void event_loop(Game& game);

/// <summary>
/// Disposes of SDL
/// </summary>
void cleanup_screen();

// Game wide getter methods
// The values they get are encapsulated in window.cpp
SDL_Window* get_window();
SDL_Renderer* get_renderer();
bool key_is_pressed(GameKeyInputs key);
SDL_FPoint get_mouse();
SDL_FPoint get_pmouse();
SDL_FPoint get_win_center();
size_t get_frame_count();
std::string_view get_exe_path();

#endif
