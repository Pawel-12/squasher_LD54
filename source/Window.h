#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "logSDLerror.h"


class Window {
private:
    unsigned int WINDOWWIDTH = 1280;
    unsigned int WINDOWHEIGHT = 800;
    SDL_Renderer * render = nullptr;
    SDL_Window * winSDL = nullptr;
public:
    Window(unsigned int ww, unsigned int wh);
    ~Window();
    unsigned int getWidth()const;
    unsigned int getHeight()const;
    SDL_Renderer * getRend()const;
    SDL_Window * getWin()const;
};
