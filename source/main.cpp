#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

#include "Window.h"
#include "Level.h"
#include "Start.h"

const unsigned int WW = 1280;
const unsigned int WH = 800;


int main(int argc, char* argv[]) {

    srand(time(nullptr));

    Window window{WW,WH};

    if((window.getRend() == nullptr) || (window.getWin() == nullptr))
        return 1;


    TickValue quit = TickValue::CONTINUE;

    while(quit != TickValue::QUIT)
    {
        Start startScreen{window};
        do{quit = startScreen.Tick();}
        while(quit == TickValue::CONTINUE);

        if(quit == TickValue::QUIT)
            break;

        Level currentLevel{window,WW,WH};
        do{quit = currentLevel.Tick();}
        while(quit == TickValue::CONTINUE);
    }

    return 0;
}