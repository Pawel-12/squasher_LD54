#include "Player.h"

Player::Player(const Cords & loc, Sprite * sprite_ptr, Window * win_ptr)
: location{loc}, sprite{sprite_ptr}, window{win_ptr}
{
    int width = 0;
    int height = 0;

    // get the size of texture
    SDL_QueryTexture(sprite->getTexture(),nullptr ,nullptr , &width, &height);
    size.w = width;
    size.h = height;
}

void Player::draw()const
{
    SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite
    SDL_RenderCopy(window->getRend(), sprite->getTexture(), nullptr, &rect);           // Copy the texture into render
}

void Player::move(const Cords & delta)
{
    float xresult = location.x + delta.x;
    float yresult = location.y + delta.y;

    if(delta.x != 0) {

        if (xresult <= 0)
            location.x = 0;
        else if ((xresult+size.w) >= window->getWidth())
            location.x = window->getWidth()-size.w;
        else
            location.x = xresult;
    }

    if(delta.y != 0) {

        if (yresult <= 0)
            location.y = 0;
        else if ((yresult+size.h) >= window->getHeight())
            location.y = window->getHeight()-size.h;
        else
            location.y = yresult;
    }
}

Cords Player::getCords()const
{
    return location;
}

void Player::setCords(const Cords & cords)
{
    location = cords;

    if(location.x < 0)
        location.x = 0;
    else if(location.x+size.w > window->getWidth())
        location.x = window->getWidth()-size.w;

    if(location.y < 0)
        location.y = 0;
    else if(location.y+size.h > window->getHeight())
        location.y = window->getHeight()-size.h;
}

Size Player::getSize()const
{
    return size;
}