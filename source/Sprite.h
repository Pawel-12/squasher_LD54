#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "logSDLerror.h"

class Sprite
{
private:
    SDL_Texture * textureSDL = nullptr;
public:
    Sprite(const char * path, SDL_Renderer * render);
    Sprite(TTF_Font * font, const char * text, const SDL_Color & color, SDL_Renderer * render);
    ~Sprite();
    Sprite & operator=(Sprite && other);
    SDL_Texture * getTexture();
};