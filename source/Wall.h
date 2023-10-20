#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>

#include "logSDLerror.h"
#include "CordsSize.h"
#include "Window.h"
#include "Sprite.h"
#include "Player.h"

class Wall {
private:
    Cords location = {0,0};
    Size size = {0,0};
    Sprite * sprite = nullptr;
    Window * window = nullptr;
    float speed = 0;
public:
    Wall(const Cords & loc, const Size & s, Sprite * sprite_ptr, Window * win_ptr, int minspeed, int basespeed = 101);
    ~Wall() = default;
    void draw()const;

    void moveX(float x)
    {
        size.w += x;
    }

    void moveX2(float x)
    {
        location.x -= x;
        size.w += x;
    }

    Cords getCords()const
    {
        return location;
    }

    Size getSize()const
    {
        return size;
    }

    float getSpeed()const
    {
        return speed;
    }

    bool col(Player & p, float deltaTime)const;
};