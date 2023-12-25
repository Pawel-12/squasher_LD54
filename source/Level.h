#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "State.h"
#include "Window.h"
#include "Sprite.h"
#include "Wall.h"
#include "Player.h"

class Level : public State
{
private:
    Window & window;
    Player player{{0,0}, nullptr, nullptr};
    std::vector<Wall> left;
    std::vector<Wall> right;
    int level = 1;
    int wallSpeed = 100;
    float wallCount = 8;
    Uint32 start_time = 0;
    unsigned int WW = 0;
    unsigned int WH = 0;
    Cords playerCords = {620,380};
    int moveX = 0;
    int moveY = 0;
    float speedModX = 100;
    float speedModY = 100;
    TTF_Font * font = nullptr;
    static std::fstream hsfile;
    void createWalls();
    void createPlayer();
public:
    Level(Window & win, unsigned int winwidth, unsigned int winheight);
    virtual ~Level();
    TickValue Tick() override;
    Level & operator++();
};