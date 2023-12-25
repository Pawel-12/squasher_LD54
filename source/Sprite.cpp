#include "Sprite.h"

Sprite::Sprite(const char * path, SDL_Renderer * render)
{
    textureSDL = IMG_LoadTexture(render, path);

    if (textureSDL == nullptr){
        std::cout << "IMG_LoadTexture: "<< IMG_GetError() << std::endl;

        //If nullptr try loading image using SDL_Surface
        SDL_Surface *sprite = IMG_Load(path);

        if (sprite == nullptr) {
            logSDLError("SDL_Surface = IMG_Load(imgpath) Error: ");
            return;
        }

        // Upload surface to renderer, and then, free the surface
        textureSDL = SDL_CreateTextureFromSurface(render, sprite);
        
        SDL_FreeSurface(sprite);

        if (textureSDL == nullptr){
            logSDLError("SDL_CreateTextureFromSurface Error: ");
            return;
        }
    }
}

Sprite::Sprite(TTF_Font * font, const char * text, const SDL_Color & color, SDL_Renderer * render)
{
    SDL_Surface * textSurface = TTF_RenderUTF8_Blended_Wrapped(font, text, color, 0);

    if (textSurface == nullptr)
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
        return;
    }
    else
    {
        textureSDL = SDL_CreateTextureFromSurface(render, textSurface);

        SDL_FreeSurface(textSurface);

        if (textureSDL == nullptr){
            logSDLError("SDL_CreateTextureFromSurface Error: ");
            return;
        }
    }
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(textureSDL);
    textureSDL = nullptr;
}

Sprite & Sprite::operator=(Sprite && other)
{
    this->~Sprite();
    textureSDL = other.textureSDL;
    other.textureSDL = nullptr;

    return *this;
}

SDL_Texture * Sprite::getTexture()
{
    return textureSDL;
}