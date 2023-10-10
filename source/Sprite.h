#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logSDLerror.h"

class Sprite
{
private:
    SDL_Texture * textSDL = nullptr;
public:
    Sprite() = default;
    Sprite(const char * path, SDL_Renderer * render);
    ~Sprite();
    SDL_Texture * getTexture();
};