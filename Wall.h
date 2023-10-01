#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const unsigned int WINDOWWIDTH = 1280;
const unsigned int WINDOWHEIGHT = 800;

void logSDLError(const std::string & msg, std::ostream & os = std::cerr);
bool setup_SDL(SDL_Window ** winSDL, SDL_Renderer ** render);
void close_SDL(SDL_Window ** winSDL, SDL_Renderer ** render);

struct Cords
{
    float x;
    float y;
};

struct Size
{
    float w;
    float h;
};

class Player
{
private:
    Cords location;
    Size size;
    SDL_Texture * img = nullptr;
    static SDL_Renderer * render;
    bool airborne = false;
public:
    Player(const Cords & loc, SDL_Texture * text, SDL_Renderer * rend)
    {
        location = loc;
        render = rend;
        img = text;

        int width = 0;
        int height = 0;

        // get the size of texture
        SDL_QueryTexture(img,nullptr ,nullptr , &width, &height);
        size.w = width;
        size.h = height;
    }
    ~Player()
    {
        SDL_DestroyTexture(img);
        img = nullptr;
    }
    void draw()const
    {
        SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite
        SDL_RenderCopy(render, img, nullptr, &rect);           // Copy the texture into render
    }

    void move(const Cords & delta)
    {
        int xresult = location.x + delta.x;
        int yresult = location.y + delta.y;

        if(delta.x != 0) {

            if (xresult <= 0)
                location.x = 0;
            else if ((xresult+size.w) >= WINDOWWIDTH)
                location.x = WINDOWWIDTH-size.w;
            else
                location.x = xresult;
        }

        if(delta.y != 0) {

            if (yresult <= 0)
                location.y = 0;
            else if ((yresult+size.h) >= WINDOWHEIGHT)
                location.y = WINDOWHEIGHT-size.h;
            else
                location.y = yresult;
        }

    }
    bool col(const SDL_Rect & arg)
    {
        SDL_Rect rect (location.x, location.y, size.w, size.h);
        if(SDL_HasIntersection(&rect,&arg))
            return true;
        else
            return false;
    }

    Cords getCords()const
    {
        return location;
    }

    void setCords(const Cords & cords)
    {
        location = cords;

        if(location.x < 0)
            location.x = 0;
        else if(location.x+size.w >WINDOWWIDTH)
            location.x = WINDOWWIDTH-size.w;

        if(location.y < 0)
            location.y = 0;
        else if(location.y+size.h >WINDOWHEIGHT)
            location.y = WINDOWHEIGHT-size.h;
    }

    Size getSize()const
    {
        return size;
    }

    void setTexture(SDL_Texture * texture)
    {
        img = texture;
    }

    bool isAirborne()const{return airborne;}
    void setAirborne(bool air){ airborne = air;}
};

class Wall {
private:
    Cords location;
    Size size;
    SDL_Texture * img = nullptr;
    static SDL_Renderer * render;
    int r;
    int g;
    int b;
    float speed;

public:
    Wall(const Cords & loc, const Size & s, SDL_Texture * text, SDL_Renderer * rend,int minspeed)
    {
        location = loc;
        size = s;
        render = rend;

        r = rand()%256;
        g = rand()%256;
        b = rand()%256;
        speed = rand()%101+minspeed;
        img = text;
    }

    ~Wall(){}

    void draw()const
    {
        /*SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite
        //SDL_RenderCopy(render, img, nullptr, &rect);         // Copy the texture into render


        SDL_SetRenderDrawColor(render,r,g,b,0);

        SDL_RenderFillRect(render, &rect);

        SDL_SetRenderDrawColor(render,0,0,0,0);
         */
        SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite
        SDL_RenderCopy(render, img, nullptr, &rect);           // Copy the texture into render
    }

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

    bool col(Player & p, float deltaTime)
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
    };
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

struct Sprite
{
    SDL_Texture * img = nullptr;
    Sprite(const char * path, SDL_Renderer * render)
    {
        img  = IMG_LoadTexture(render, path);
        if (img == nullptr){
            std::cout<<"IMG_LoadTexture: "<<IMG_GetError()<<std::endl;

            //If nullptr try loading image using SDL_Surface
            SDL_Surface *sprite = IMG_Load(path);
            if (sprite == nullptr) {
                logSDLError("SDL_Surface = IMG_Load(imgpath) Error: ");
                return ;
            }

            // Upload surface to renderer, and then, free the surface
            img = SDL_CreateTextureFromSurface(render, sprite);
            SDL_FreeSurface(sprite);
            if (img == nullptr){
                logSDLError("SDL_CreateTextureFromSurface Error: ");
                return ;
            }
        }
    }
    ~Sprite()
    {
        SDL_DestroyTexture(img);
        img = nullptr;
    }
};