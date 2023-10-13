#include <SDL2/SDL.h>

#ifndef _GAME_RENDERABLE_H
#define _GAME_RENDERABLE_H

class Renderable {
public:
    virtual void render(SDL_Renderer* render) const = 0;
};

#endif
