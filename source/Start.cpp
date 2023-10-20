#include "Start.h"

Start::Start(Window & win) : window{win}
{
    startscreen = std::make_unique<Sprite>("../data/titlescreen.png", win.getRend());
    font = TTF_OpenFont("../data/ChakraPetch-Bold.ttf", 175);
}

Start::~Start()
{
    TTF_CloseFont(font);
}

TickValue Start::Tick()
{
    SDL_Event e;

    //start_time = SDL_GetTicks();

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            return TickValue::QUIT;
        if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN)
            return TickValue::NEXTSTATE;
    }

    SDL_Rect rect (0,0, 1280, 800);
    SDL_RenderCopy(window.getRend(), (*startscreen).getTexture(), nullptr, &rect);

    SDL_RenderPresent(window.getRend());
    SDL_RenderClear(window.getRend());

    auto temp = SDL_GetTicks();

    if( (1000/60) > (SDL_GetTicks() - start_time) )                                             // 60 FPS
    {
        SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
    }

    start_time = temp;
    
    return TickValue::CONTINUE;
}