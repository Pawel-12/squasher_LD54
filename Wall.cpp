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
        *render = SDL_CreateRenderer(*winSDL, -1, SDL_RENDERER_ACCELERATED/*|SDL_RENDERER_PRESENTVSYNC*/);

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
