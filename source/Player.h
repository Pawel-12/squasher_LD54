#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "CordsSize.h"
#include "Window.h"
#include "Sprite.h"

class Player
{
private:
    Cords location{0,0};
    Size size{0,0};
    Sprite * sprite = nullptr;
    Window * window = nullptr;
public:
    Player(const Cords & loc, Sprite * sprite_ptr, Window * win_ptr);
    ~Player() = default;
    void draw()const;
    void move(const Cords & delta);
    /*
    bool col(const SDL_Rect & arg)
    {
        SDL_Rect rect (location.x, location.y, size.w, size.h);
        if(SDL_HasIntersection(&rect,&arg))
            return true;
        else
            return false;
    }
    */
    Cords getCords()const;
    void setCords(const Cords & cords);
    Size getSize()const;
};