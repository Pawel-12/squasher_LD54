#include <fstream>
#include "Start.h"

Start::Start(Window & win) : window{win}
{
    startscreen = std::make_unique<Sprite>("../data/titlescreen.png", win.getRend());
    font = TTF_OpenFont("../data/ChakraPetch-Bold.ttf", 30);

    TTF_SetFontWrappedAlign(font, TTF_WRAPPED_ALIGN_CENTER);

    std::fstream hsfile("highscore.txt", std::ios::in);

    if(!hsfile)
        std::cout << "Error while opening file\n";

    int hs = 0;

    if(!hsfile.eof())
        hsfile >> hs;

    hsfile.close();

    textSprite = std::make_unique<Sprite>(font, ("HIGH SCORE \n" + std::to_string(hs)).c_str(), SDL_Color{0,0,0,255}, window.getRend());
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
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
            return TickValue::QUIT;
        if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_KEYDOWN)
            return TickValue::NEXTSTATE;
    }

    SDL_Rect rect (0,0, 1280, 800);
    SDL_RenderCopy(window.getRend(), (*startscreen).getTexture(), nullptr, &rect);

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(textSprite->getTexture(), nullptr, nullptr, &textW, &textH);
    SDL_Rect textRect((window.getWidth() - textW)/2, (window.getHeight() - textH)/1.1, textW, textH);

    SDL_RenderCopy(window.getRend(), textSprite->getTexture(), nullptr, &textRect);

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