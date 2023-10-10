#include "Sprite.h"

Sprite::Sprite(const char * path, SDL_Renderer * render)
{
    textSDL = IMG_LoadTexture(render, path);

    if (textSDL == nullptr){
        std::cout << "IMG_LoadTexture: "<< IMG_GetError() << std::endl;

        //If nullptr try loading image using SDL_Surface
        SDL_Surface *sprite = IMG_Load(path);

        if (sprite == nullptr) {
            logSDLError("SDL_Surface = IMG_Load(imgpath) Error: ");
            return;
        }

        // Upload surface to renderer, and then, free the surface
        textSDL = SDL_CreateTextureFromSurface(render, sprite);
        
        SDL_FreeSurface(sprite);

        if (textSDL == nullptr){
            logSDLError("SDL_CreateTextureFromSurface Error: ");
            return;
        }
    }
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(textSDL);
    textSDL = nullptr;
}

SDL_Texture * Sprite::getTexture()
{
    return textSDL;
}