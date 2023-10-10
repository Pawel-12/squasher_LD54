#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>

#include "Window.h"
#include "Sprite.h"
#include "Wall.h"
#include "Player.h"

const unsigned int WW = 1280;
const unsigned int WH = 800;

int main(int argc, char* argv[]) {

    srand(time(NULL));

    Window window{WW,WH};

    if((window.getRend() == nullptr) || (window.getWin() == nullptr))
        return 1;


    Sprite forkLeft("widlav2.png",window.getRend());
    Sprite forkRight("widla2v2.png",window.getRend());
    Sprite background("backgroundsq.png",window.getRend());
    Sprite dynia("dynia.png",window.getRend());


    std::vector<Wall> left;
    std::vector<Wall> right;

    int level = 1;
    int wallSpeed = 100;
    float wallCount = 8;

    nextlvl:
    SDL_WarpMouseInWindow(window.getWin(),640,400);
    
    float wallHeight = ceilf(WH/wallCount);
    Size wallSize = {50,wallHeight};

    for(int i = 0; i < wallCount; i++)
    {
        left.push_back({{0,i*wallHeight}, wallSize, &forkLeft, &window, wallSpeed});
        right.push_back({{1230,i*wallHeight}, wallSize, &forkRight, &window, wallSpeed});
    }

    int space = rand()%(static_cast<int>(2*wallCount-1));

    if(space >= wallCount)
        right.erase(right.begin() + space % static_cast<int>(wallCount));
    else
        left.erase(left.begin() + space);

    Player player({620,380}, &dynia, &window);

    SDL_Event e;
    bool quit = false;

    unsigned int start_time = SDL_GetTicks();                                                       // get start time
    while (!quit){
        //int moveX = 0;
        //int moveY = 0;

      while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                quit = true;

             if (e.type == SDL_MOUSEMOTION)
             {
                 player.setCords(Cords(e.motion.x-20, e.motion.y-20));
             }
        }

        /*const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        if(currentKeyStates[SDL_SCANCODE_W] && !player.isAirborne()) {
            moveY = -1;
            player.setAirborne(true);
            jumptimer = 0.3;
        }


        if(currentKeyStates[SDL_SCANCODE_A])
            moveX = -1;
        else if (currentKeyStates[SDL_SCANCODE_D])
            moveX = 1;


        //std::cout << delta<<'\n';

        if(player.getCords().y + 40 < WINDOWHEIGHT)
        {
            //player.move({0,1100.F * delta});
        }
        else
            player.setAirborne(false);

        if(jumptimer > 0)
        {
            player.move({0,-1 * 1700.F * delta });
            jumptimer -= delta;
        }
        else
            jumptimer = 0;

*/
        SDL_Rect rect (0,0, 1280, 800);                            // create rect with size of sprite
        SDL_RenderCopy(window.getRend(), background.getTexture(), nullptr, &rect);

        int moving = 0;

        float delta = (SDL_GetTicks() - start_time)/1000.0;
        for(auto& wall : left)
        {
            if(wall.getCords().x + wall.getSize().w < (WW/2))
            {
                wall.moveX(delta * wall.getSpeed());
                moving = 1;
            }

            if(wall.col(player,delta))
            {
                SDL_Delay(1000);
                return 3;
            }

            }

        for(auto& wall : right)
        {
            if(wall.getCords().x > (WW/2))
            {
                wall.moveX2(delta * wall.getSpeed());
                moving = 1;
            }

            if(wall.col(player,delta))
            {
                SDL_Delay(1000);
                return 3;
            }

        }

        if (!moving)
        {
            right.clear();
            left.clear();
            if(wallCount < 12)
                wallCount += 2;
            else
                wallSpeed += 25;
            level++;
            std::cout <<"Level nr. "<< level <<"\n";

            goto nextlvl;
        }


/*
        Player tempplayer = player;
        tempplayer.setTexture(nullptr);
        tempplayer.move({moveX * 20.F, 0});

        float colCords = 0;
        for (auto &wall: left) {
            auto cords = wall.getCords();
            auto size = wall.getSize();
            /*std::cout << cords.x << " " << cords.y << " " << size.w << " " << size.h << "   "
                      << player.getCords().x << " " << player.getCords().y << " " << player.getSize().w << " "
                      << player.getSize().h << '\n';
            if (wall.col(tempplayer, delta)) {

                colCords = wall.getCords().x + wall.getSize().w;
                //std::cout << colCords << '\n';
                break;
            }
        }

        for (auto &wall: right) {
            auto cords = wall.getCords();
            auto size = wall.getSize();



            if (wall.col(tempplayer, delta)) {

                if(colCords)
                    return 3;

                colCords = wall.getCords().x-player.getSize().w;
                //std::cout << colCords << '\n';
                break;
            }
        }
        if (colCords)
            player.setCords({colCords, player.getCords().y});
        else
            player.move({moveX * 20.F, 0});
        */
        /*else if(moveX > 0)
        {
            float colCords = 0;
            for(auto& wall: right)
            {
                auto cords = wall.getCords();
                auto size = wall.getSize();
                if(player.col(SDL_Rect(cords.x,cords.y,size.w,size.h)))
                {
                    colCords = wall.getCords().x - player.getSize().w;
                    std::cout<<colCords<<'\n';
                    break;
                }
            }
            if(colCords)
                player.setCords({colCords,player.getCords().y});
            else
                player.move({moveX * 20.F,0});
        }
*/


        player.draw();

        for(const auto& wall : left)
            wall.draw();

        for(const auto& wall : right)
            wall.draw();


        SDL_RenderPresent(window.getRend());
        SDL_RenderClear(window.getRend());


        auto temp = SDL_GetTicks();

        if( (1000/60) > (SDL_GetTicks() - start_time) )                                             // 60 FPS
        {
            SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
        }
        start_time = temp;
    }

    return 0;
}
