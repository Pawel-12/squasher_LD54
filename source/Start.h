#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <memory>

#include "State.h"
#include "Window.h"
#include "Sprite.h"
#include "Wall.h"
#include "Player.h"

class Start : public State
{
private:
    Window & window;
    std::unique_ptr<Sprite> startscreen;
    Uint32 start_time = 0;
    TTF_Font * font = nullptr;
public:
    Start(Window & win);
    virtual ~Start();
    virtual TickValue Tick() override;
};
