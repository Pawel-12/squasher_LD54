#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "logSDLerror.h"
#include "CordsSize.h"
#include "Window.h"
#include "Sprite.h"
#include "Player.h"



//void logSDLError(const std::string & msg, std::ostream & os = std::cerr);
//bool setup_SDL(SDL_Window ** winSDL, SDL_Renderer ** render);
//void close_SDL(SDL_Window ** winSDL, SDL_Renderer ** render);


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

   /* bool colY(Player & p, float deltaTime)
    {
        //SDL_Rect rect (location.x, location.y, size.w, size.h);
        //SDL_Rect playerrect (p.getCords().x, p.getCords().y, p.getSize().w, p.getSize().h);
        //if(SDL_HasIntersection(&rect,&playerrect))
        auto px = p.getCords().x;
        auto py = p.getCords().y;

        bool MID = (py+p.getSize().h >= location.y) && ((py+p.getSize().h) <= (location.y+size.h));
        bool MID2 = (py <= (location.y+size.h)) && ((py) >= (location.y));

        bool L = (px <= (location.x+size.w)) && (px >= location.x);
        bool R = ((px+p.getSize().w) >= (location.x)) && (px+p.getSize().w) <= (location.x+size.w);

        bool LR = (px >= location.x) && ((px+p.getSize().w) <= (location.x+size.w));


        if(LR )
        {
            if(location.x < p.getCords().x)
            {
                p.setCords({location.x+size.w, p.getCords().y});
            }
            else if(location.x > p.getCords().x)
            {
                p.setCords({location.x-p.getSize().w, p.getCords().y});
            }

            //p.move({X*100*deltaTime,0});
            return true;
        }
        return false;
    };*/
};