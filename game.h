#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "includes.h"

class game
{
private :
    bool Running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event Event;
    int screenWidth, screenHeight;
    SDL_Rect displayRect;

    SDL_Texture* background;
    SDL_Rect rectBackground;

    TTF_Font *font;
    SDL_Surface *message;
    SDL_Texture *text;
    SDL_Rect textRect;
    SDL_Color textColor;

    std::string data;
    bool typing;

public:
    game();
    int OnExecute();
    bool OnInit();
    bool LoadContent();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void Cleanup();
};


#endif // GAME_H_INCLUDED
