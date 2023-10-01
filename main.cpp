#include <iostream>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Wall.h"

int main(int argc, char* argv[]) {

    srand(time(NULL));

    SDL_Renderer * render = nullptr;
    SDL_Window * window = nullptr;

    if(!setup_SDL(&window, &render))
        return 1;

    nextlvl:
    Sprite widla("widlav2.png",render);
    Sprite widla2("widla2v2.png",render);
    Sprite background("backgroundsq.png",render);
    Sprite dynia("dynia.png",render);

    std::vector<Wall> left;
    std::vector<Wall> right;
    static int level = 1;
    static int speed = 100;
    static float wallscount = 8;

    SDL_WarpMouseInWindow(window,640,400);

    for(int i = 0; i < wallscount; i++)
    {
        left.push_back({{0,(i/wallscount)*WINDOWHEIGHT},{50, ceilf(WINDOWHEIGHT/wallscount)},widla.img,render,speed});
        right.push_back({{1230,(i/wallscount)*WINDOWHEIGHT},{50,ceilf(WINDOWHEIGHT/wallscount)},widla2.img,render,speed});
    }
    int space = rand()%(static_cast<int>(2*wallscount-1));

    if(space >= wallscount)
        right.erase(right.begin() + space%static_cast<int>(wallscount));
    else
        left.erase(left.begin() + space);

    Player player({620,380},dynia.img, render);

    SDL_Event e;
    bool quit = false;
    //float jumptimer = 0;

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
        SDL_RenderCopy(render, background.img, nullptr, &rect);

        int moving = 0;

        float delta = (SDL_GetTicks() - start_time)/1000.0;
        for(auto& wall : left)
        {
            if(wall.getCords().x + wall.getSize().w < (WINDOWWIDTH/2))
            {
                wall.moveX(delta * wall.getSpeed());
                moving = 1;
            }

            if(wall.col(player,delta))
                return 3;
            }

        for(auto& wall : right)
        {
            if(wall.getCords().x > (WINDOWWIDTH/2))
            {
                wall.moveX2(delta * wall.getSpeed());
                moving = 1;
            }

            if(wall.col(player,delta))
                return 3;

        }

        if (!moving)
        {
            right.clear();
            left.clear();
            if(wallscount < 12)
                wallscount += 2;
            else
                speed += 25;
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

        SDL_SetRenderDrawColor(render,0,255,0,0);

        //SDL_Rect rect(50,50,50,50);
        //SDL_RenderFillRect(render, &rect);
        //SDL_RenderDrawRect(render, &rect);

        //SDL_RenderDrawLine(render,640,0,640,800);

        SDL_SetRenderDrawColor(render,0,0,0,0);


        player.draw();

        for(const auto& wall : left)
            wall.draw();

        for(const auto& wall : right)
            wall.draw();


        SDL_RenderPresent(render);
        SDL_RenderClear(render);


        auto temp = SDL_GetTicks();

        if( (1000/60) > (SDL_GetTicks() - start_time) )                                             // 60 FPS
        {
            SDL_Delay((1000/60)-(SDL_GetTicks()-start_time));
        }
        start_time = temp;
    }



    close_SDL(&window, &render);
    return 0;
}
