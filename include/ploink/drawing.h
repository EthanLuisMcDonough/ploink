#ifndef _GAME_DRAWING_H
#define _GAME_DRAWING_H

#include "ploink/vec.h"
#include "SDL.h"

/// <summary>
/// Renders a circle.
/// </summary>
/// <param name="renderer">SDL renderer</param>
/// <param name="center">Circle center</param>
/// <param name="radius">Circle radius</param>
void draw_circle(SDL_Renderer* renderer, Vec center, float radius);

#endif
