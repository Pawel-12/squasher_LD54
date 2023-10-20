#include "Wall.h"

Wall::Wall(const Cords & loc, const Size & s, Sprite * sprite_ptr, Window * win_ptr, int minspeed, int basespeed)
: location{loc}, size{s}, sprite{sprite_ptr}, window{win_ptr}
{
    speed = (rand() % basespeed) + minspeed;
}

void Wall::draw()const
{
    SDL_Rect rect (location.x, location.y, ceilf(size.w), ceilf(size.h));                            // create rect with size of sprite
    SDL_RenderCopy(window->getRend(), sprite->getTexture(), nullptr, &rect);           // Copy the texture into render
}

bool Wall::col(Player & p, float deltaTime)const
{
    // SDL_Rect rect (location.x, location.y, size.w, size.h);
    //SDL_Rect playerrect (p.getCords().x, p.getCords().y, p.getSize().w, p.getSize().h);
    // if(SDL_HasIntersection(&rect,&playerrect))
    //     return true;

    auto px = p.getCords().x;
    auto py = p.getCords().y;

    //bool MID = (py+p.getSize().h > location.y) && ((py+p.getSize().h) < (location.y+size.h));
    bool MID2 = (py <= (location.y+size.h)) && ((py) >= (location.y));
    bool MID = (py+p.getSize().h >= location.y) && ((py+p.getSize().h) <= (location.y+size.h));

    bool L = (px <= (location.x+size.w)) && (px >= location.x);
    bool R = ((px+p.getSize().w) >= (location.x)) && (px+p.getSize().w) <= (location.x+size.w);
    bool LR = (px >= location.x) && ((px+p.getSize().w) <= (location.x+size.w));
    if((MID||MID2) && (L || R))
    {
        if(location.x < p.getCords().x)
        {
            //p.setCords({location.x+size.w, p.getCords().y});
        }
        else if(location.x > p.getCords().x)
        {
            //p.setCords({location.x-p.getSize().w, p.getCords().y});
        }

        //p.move({X*100*deltaTime,0});
        return true;
    }
    return false;
}