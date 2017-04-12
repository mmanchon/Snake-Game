#include"game.h"

bool game::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0)
    {
        return false;
    }

    if(window = SDL_CreateWindow("Texto",100,100,screenWidth,screenHeight,SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)==NULL)
    {
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout<<SDL_GetError()<<std::endl;
        return false;
    }
    if(TTF_Init() == -1)
    {
        return flase;

    }

    return true;
}
