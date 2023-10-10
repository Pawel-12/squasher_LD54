
/*
#include "Wall.h"

SDL_Renderer * Wall::render = nullptr;
SDL_Renderer * Player::render = nullptr;

void logSDLError(const std::string & msg, std::ostream & os){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

bool setup_SDL(SDL_Window ** winSDL, SDL_Renderer ** render)
{
    //Initialize SDL subsystems
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        logSDLError("SDL could not initialize! SDL_Error: ");
        return false;
    }
    else
    {
        // Create window
        *winSDL = SDL_CreateWindow( "SQUASHER!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);

        // if create window failed
        if(*winSDL == nullptr)
        {
            logSDLError("Window could not be created! SDL_Error: ");
            return false;
        }

        // create SDL renderer
        *render = SDL_CreateRenderer(*winSDL, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC);

        SDL_ShowCursor(SDL_DISABLE);

        // if create renderer failed
        if (*render == nullptr)
        {
            logSDLError("SDL_CreateRenderer Error:");
            return false;
        }

        SDL_SetRenderDrawColor(*render, 0, 0, 0, 255);          // Set renderer color
        SDL_RenderClear(*render);                                          // Fill renderer with color
        SDL_RenderPresent(*render);                                        // Show renderer on window

        //Initialize SDL_image subsystems
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            std::cout<<"IMG_INIT: "<<IMG_GetError()<<std::endl;
            return false;
        }
    }
    return true;
}

void close_SDL(SDL_Window ** winSDL, SDL_Renderer ** render)
{
    //Destroy window
    SDL_DestroyWindow(*winSDL);
    *winSDL = nullptr;

    // destroy renderer
    SDL_DestroyRenderer(*render);
    *render = nullptr;

    //Quit SDL IMG
    IMG_Quit();

    //Quit SDL subsystems
    SDL_Quit();
}
*/

#include "Wall.h"


Wall::Wall(const Cords & loc, const Size & s, Sprite * sprite_ptr, Window * win_ptr, int minspeed, int basespeed)
: location{loc}, size{s}, sprite{sprite_ptr}, window{win_ptr}
{
    speed = (rand() % basespeed) + minspeed;
}

void Wall::draw()const
{
    /*SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite

    SDL_SetRenderDrawColor(render,r,g,b,0);

    SDL_RenderFillRect(render, &rect);

    SDL_SetRenderDrawColor(render,0,0,0,0);
     */
    SDL_Rect rect (location.x, location.y, size.w, size.h);                            // create rect with size of sprite

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