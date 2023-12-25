#include <fstream>
#include "Level.h"

std::fstream Level::hsfile;

void Level::createWalls()
{
    static Sprite forkLeft("../data/forkleft.png",window.getRend());
    static Sprite forkRight("../data/forkright.png",window.getRend());

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
}

void Level::createPlayer()
{
    static Sprite dynia("../data/dynia.png",window.getRend());
    player = Player({620,380}, &dynia, &window);
}

Level::Level(Window & win, unsigned int winwidth, unsigned int winheight) : window{win}, WW{winwidth}, WH(winheight)
{
    font = TTF_OpenFont("../data/ChakraPetch-Bold.ttf", 100);

    hsfile.open("highscore.txt", std::ios::in);

    if(!hsfile)
        std::cout << "Error while opening file\n";

    createPlayer();
    createWalls();
    start_time = SDL_GetTicks();
}

Level::~Level()
{
    TTF_CloseFont(font);

    int temp = 0;
    if(!hsfile.eof())
        hsfile >> temp;

    if(level > temp)
    {
        hsfile.close();
        hsfile.open("highscore.txt", std::ios::out | std::ios::trunc);

        if(hsfile)
            hsfile << level;
        else
            std::cout << "Error while opening file\n";

        std::cout << "New highscore = " << level << '\n';
    }
    hsfile.close();
}

TickValue Level::Tick()
{
    static Sprite background("../data/backgroundsq.png",window.getRend());
    static Sprite gameover("../data/gameoverscreen.png",window.getRend());
    static Sprite textSprite(font, "1", {0,0,0,255}, window.getRend());

    int textW = 0;
    int textH = 0;

    SDL_QueryTexture(textSprite.getTexture(), nullptr, nullptr, &textW, &textH);
    SDL_Rect textRect((WW - textW)/2, (WH - textH)/2, textW, textH);

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.window.event == SDL_WINDOWEVENT_LEAVE)
        {
            playerCords = player.getCords();
        }
        else if (e.window.event  == SDL_WINDOWEVENT_ENTER)
        {
            SDL_WarpMouseInWindow(window.getWin(),playerCords.x + 20, playerCords.y + 20);
            player.setCords(playerCords);

            while((SDL_PollEvent(&e)))
                continue;

            break;
        }
        else if (e.type == SDL_MOUSEMOTION)
        {
            player.setCords(Cords(e.motion.x-20, e.motion.y-20));
        }
        else if (e.type == SDL_QUIT)
            return TickValue::QUIT;
    }

    int tempX = moveX;
    int tempY = moveY;

    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if(currentKeyStates[SDL_SCANCODE_A] || currentKeyStates[SDL_SCANCODE_LEFT])
        moveX = -1;
    else if (currentKeyStates[SDL_SCANCODE_D] || currentKeyStates[SDL_SCANCODE_RIGHT])
        moveX = 1;
    else
        moveX = 0;


    if(currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP])
        moveY = -1;
    else if (currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_DOWN])
        moveY = 1;
    else
        moveY = 0;


    if((moveX == tempX) && (moveX && tempX))
        speedModX += 20;
    else
        speedModX = 100;

    if((moveY == tempY) && (moveY && tempY))
        speedModY += 20;
    else
        speedModY = 100;


    float delta = (SDL_GetTicks() - start_time)/1000.0;

    player.move({moveX * speedModX * delta, moveY * speedModY * delta});

    SDL_Rect rect (0,0, 1280, 800);                            // create rect with size of sprite
    SDL_RenderCopy(window.getRend(), background.getTexture(), nullptr, &rect);

    SDL_RenderCopy(window.getRend(), textSprite.getTexture(), nullptr, &textRect);

    bool wallsMoving = false;

    for(auto& wall : left)
    {
        if(wall.getCords().x + wall.getSize().w < (WW/2))
        {
            wall.moveX(delta * wall.getSpeed());
            wallsMoving = true;
        }

        if(wall.col(player,delta))
        {
            SDL_Delay(1000);

            SDL_RenderCopy(window.getRend(), gameover.getTexture(), nullptr, &rect);
            SDL_Rect tempTextRect{509 + ((262-textRect.w)/2), 398, textRect.w, textRect.h};

            SDL_RenderCopy(window.getRend(), textSprite.getTexture(), nullptr, &tempTextRect);

            SDL_RenderPresent(window.getRend());
            SDL_RenderClear(window.getRend());

            SDL_Delay(1750);
            // reset score counter
            textSprite = Sprite(font, "1", {0,0,0,255}, window.getRend());

            while((SDL_PollEvent(&e)))
                continue;

            return TickValue::NEXTSTATE;
        }
        wall.draw();
    }

    for(auto& wall : right)
    {
        if(wall.getCords().x > (WW/2))
        {
            wall.moveX2(delta * wall.getSpeed());
            wallsMoving = true;
        }

        if(wall.col(player,delta))
        {
            SDL_Delay(1000);

            SDL_RenderCopy(window.getRend(), gameover.getTexture(), nullptr, &rect);
            SDL_Rect tempTextRect{509 + ((262-textRect.w)/2), 398, textRect.w, textRect.h};

            SDL_RenderCopy(window.getRend(), textSprite.getTexture(), nullptr, &tempTextRect);

            SDL_RenderPresent(window.getRend());
            SDL_RenderClear(window.getRend());

            SDL_Delay(1750);
            // reset score counter
            textSprite = Sprite(font, "1", {0,0,0,255}, window.getRend());

            while((SDL_PollEvent(&e)))
                continue;

            return TickValue::NEXTSTATE;
        }
        wall.draw();
    }

    if (!wallsMoving)
    {
        ++(*this);

        textSprite = Sprite(font, std::to_string(level).c_str(), {0,0,0,255}, window.getRend());

        return TickValue::CONTINUE;
    }

    player.draw();

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

Level & Level::operator++()
{
    right.clear();
    left.clear();

    if(wallCount < 12)
        wallCount += 2;
    else
        wallSpeed += 25;
    level++;
    std::cout <<"Level nr. "<< level <<"\n";

    createWalls();

    speedModX = speedModY = 100;
    moveX = moveY = 0;
    playerCords = {620,380};

    return *this;
}