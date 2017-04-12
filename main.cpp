#include <SDL.h>
#include <stdio.h>
#include<iostream>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdint.h>
#include <sstream>
#include <cstdlib>
#include <ctime>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
using namespace std;

bool init();
void close();

bool direccio [4] = {false,false,false,false};
SDL_Rect posicioCua[460];
int tail =0;

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

SDL_Texture* texture = NULL;

SDL_Texture* aux = NULL;

SDL_Texture* fruta_t = NULL;

SDL_Texture* tail_t = NULL;

SDL_Texture* puntuacio = NULL;

SDL_Texture* score = NULL;

SDL_Texture* vidas_t = NULL;

SDL_Texture* corazones_t = NULL;

SDL_Surface* text_surface = NULL;
SDL_Surface* tiempo_surface = NULL;

SDL_Texture* tiempo_t = NULL;

SDL_Color text_color = {0,0,0};

string fontpath = "arial.ttf";
string text="0",ttotal="0:00";
stringstream ss;


TTF_Font* font = NULL;

unsigned int startTime = 0;

time_t startgame;

bool start = false;

SDL_Rect rect,fruta,punt;

int tiempo = 500,sjugado=0,mjugado=0;
int scr = 0,corazones = 3;



SDL_Rect loadTexture(std::string path,SDL_Rect s_rect)
{
    std::string snake ("snake.png");
    std::string cuerpo("cuerpo.png");
    std::string gameover("game over.png");

    if(path.compare(snake)==0)
    {
        texture = IMG_LoadTexture(renderer,"snake.png");
        s_rect.x = 0;
        s_rect.y = 0;
        s_rect.w = SCREEN_WIDTH;
        s_rect.h = SCREEN_HEIGHT;
    }
    if(path.compare(gameover)==0)
    {
        texture = IMG_LoadTexture(renderer,"game over.png");
        aux = NULL;
        s_rect.x = 0;
        s_rect.y = 0;
        s_rect.w = SCREEN_WIDTH;
        s_rect.h = SCREEN_HEIGHT;
    }
    if(path.compare(cuerpo)==0)
    {
        texture = IMG_LoadTexture(renderer,"cuerpo.png");
        aux = IMG_LoadTexture(renderer,"bloque.png");
        s_rect.x = 320;
        s_rect.y = 240;
        s_rect.w = 20;
        s_rect.h = 20;
    }
    return s_rect;
}

void update(SDL_Rect s_rect,SDL_Rect fruta)
{
    SDL_RenderClear(renderer);
    if(aux!=NULL)
    {
        rect.x = 0;
        rect.y = 0;
        rect.w = 20;
        rect.h = 20;

        text_surface = TTF_RenderText_Solid(font, text.c_str(),text_color);
        score = SDL_CreateTextureFromSurface(renderer,text_surface);

        for(int i =0; i<tail;i++)
        {
            SDL_RenderCopy(renderer,tail_t,NULL,&posicioCua[i]);
        }

        punt.x = 420;
        punt.y = 20;
        punt.w = 200;
        punt.h = 80;
        SDL_RenderCopy(renderer,puntuacio,NULL,&punt);

        punt.y = 100;
        punt.w = 80;
        punt.x = 540;
        SDL_RenderCopy(renderer,score,NULL,&punt);

        punt.y = 180;
        punt.w = 200;
        punt.x = 420;
        SDL_RenderCopy(renderer,vidas_t,NULL,&punt);

        punt.y = 260;
        SDL_RenderCopy(renderer,corazones_t,NULL,&punt);

        punt.y = 340;
        SDL_RenderCopy(renderer,tiempo_t,NULL,&punt);

        for(int i=0;i<31;i++)
        {
            rect.x = rect.x+20;
            SDL_RenderCopy(renderer,aux,NULL,&rect);
        }
        for(int i=0;i<23;i++)
        {
            rect.y = rect.y +20;
            SDL_RenderCopy(renderer,aux,NULL,&rect);
        }
        for(int i=0;i<31;i++)
        {
            rect.x = rect.x -20;
            SDL_RenderCopy(renderer,aux,NULL,&rect);
        }
        for(int i=0;i<23;i++)
        {
            rect.y = rect.y-20;
            SDL_RenderCopy(renderer,aux,NULL,&rect);
        }
        rect.x = 400;
        rect.y = 0;
        for(int i=0;i<23;i++)
        {
            rect.y = rect.y +20;
            SDL_RenderCopy(renderer,aux,NULL,&rect);
        }

        SDL_RenderCopy(renderer,fruta_t,NULL,&fruta);

    }
    SDL_RenderCopy(renderer,texture,NULL,&s_rect);
    SDL_RenderPresent(renderer);
}

SDL_Rect updateDireccio(SDL_Rect s_rect)
{

    int prevX = posicioCua[0].x;
    int prevY = posicioCua[0].y;
    int prev2x, prev2y;
    posicioCua[0].x = s_rect.x;
    posicioCua[0].y = s_rect.y;

    for(int i =1; i<tail;i++)
    {
        prev2x = posicioCua[i].x;
        prev2y = posicioCua[i].y;
        posicioCua[i].x = prevX;
        posicioCua[i].y = prevY;
        prevX = prev2x;
        prevY = prev2y;
    }

    if(direccio[0])
    {
        s_rect.x = s_rect.x;
        s_rect.y = s_rect.y-20;
        s_rect.w = s_rect.w;
        s_rect.h = s_rect.h;
    }
    if(direccio[1])
    {
        s_rect.x = s_rect.x;
        s_rect.y = s_rect.y+20;
        s_rect.w = s_rect.w;
        s_rect.h = s_rect.h;
    }
    if(direccio[2])
    {
        s_rect.x = s_rect.x-20;
        s_rect.y = s_rect.y;
        s_rect.w = s_rect.w;
        s_rect.h = s_rect.h;
    }
    if(direccio[3])
    {
        s_rect.x = s_rect.x+20;
        s_rect.y = s_rect.y;
        s_rect.w = s_rect.w;
        s_rect.h = s_rect.h;
    }


    return s_rect;
}

SDL_Rect fruita()
{
    fruta.h = 20;
    fruta.w = 20;
    fruta.y = rand() % 420 +20;
    fruta.x = rand() % 360 +20;
    fruta.x = (fruta.x /10)*10;
    fruta.y = (fruta.y /10)*10;
    if(fruta.x % 20 != 0)
    {
        fruta.x += 10;
    }
    if(fruta.y % 20 != 0)
    {
        fruta.y +=10;
    }
    return fruta;
}

bool comprovacio(SDL_Rect rect)
{
    if((rect.y < 20 || rect.y > 440) && rect.y != 0)
    {
        start = false;
        tiempo = 500;
        corazones--;
        return false;
    }
    if((rect.x < 20 || rect.x > 380) && rect.y != 0)
    {
        start = false;
        tiempo = 500;
        corazones--;
        return false;
    }

    if(rect.x == fruta.x && rect.y == fruta.y)
    {
        fruta = fruita();
        tail++;
        scr += 10;
        ss.str(string());
        ss.clear();
        ss<<scr;
        text = "";
        text = ss.str();
        if(tiempo>100)
        {
            tiempo -= 50;
        }
    }

    for(int i=0;i<tail;i++)
    {
        if(rect.x == posicioCua[i].x && rect.y == posicioCua[i].y)
        {
            return false;
        }
    }
    return true;
}

time_t timeGET()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    return rawtime;
}

void diferenciaTiempo()
{
    time_t rawtime;
    struct tm* timeinfo,auxTime;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    double diferencia;
    diferencia *= -1;
    diferencia = difftime(startgame,mktime(timeinfo));
    diferencia *= -1;
    sjugado = diferencia;
    if(sjugado>59)
    {
        mjugado++;
        sjugado = 0;
        startgame = timeGET();
    }
    stringstream saux,saux2;
    saux<<sjugado;
    saux2<<mjugado;
    ttotal = saux2.str() + ":" + saux.str();

}



int main (int argc, char* args[])
{
    bool quit = false;
    SDL_Event e;
    SDL_Rect s_rect;
    int anterior;
    ss<<scr;

    if(!init())
    {
        printf("Error en inicializar!");

    }
    else
    {
        font = TTF_OpenFont(fontpath.c_str(),20);
        startTime = SDL_GetTicks();
        s_rect = loadTexture("snake.png",s_rect);
        fruta_t = IMG_LoadTexture(renderer,"platano.png");
        corazones_t = IMG_LoadTexture(renderer,"corazones.png");
        fruta = fruita();
        text = ss.str();
        startgame = timeGET();

            while(!quit && corazones!=0)
            {
                diferenciaTiempo();
                tiempo_surface = TTF_RenderText_Solid(font, ttotal.c_str(),text_color);
                tiempo_t = SDL_CreateTextureFromSurface(renderer,tiempo_surface);
                if(comprovacio(s_rect))
                {
                    if(start && SDL_GetTicks()-startTime>tiempo){
                        s_rect = updateDireccio(s_rect);
                        update(s_rect,fruta);
                        startTime = SDL_GetTicks();
                    }
                    else
                    {
                        update(s_rect,fruta);
                    }

                    //va vaciando la cola
                    while(SDL_PollEvent(&e) != 0)
                    {
                        if(e.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                        else if(e.type == SDL_KEYDOWN)
                        {

                            switch(e.key.keysym.sym)
                            {
                                case SDLK_UP:
                                    if(start&&anterior!=1)
                                    {
                                        for(int i=0;i<4;i++)
                                        {
                                            direccio[i] = false;
                                        }
                                        direccio[0] = true;
                                        anterior = 0;
                                    }
                                break;
                                case SDLK_DOWN:
                                    if(start&&anterior!=0)
                                    {
                                        for(int i=0;i<4;i++)
                                        {
                                            direccio[i] = false;
                                        }
                                        direccio[1] = true;
                                        anterior = 1;
                                    }
                                break;
                                case SDLK_LEFT:
                                    if(start && anterior !=3)
                                    {
                                        for(int i=0;i<4;i++)
                                        {
                                            direccio[i] = false;
                                        }
                                        direccio[2] = true;
                                        anterior = 2;
                                    }
                                break;
                                case SDLK_RIGHT:
                                    if(start && anterior != 2)
                                    {
                                        for(int i=0;i<4;i++)
                                        {
                                            direccio[i] = false;
                                        }
                                        direccio[3] = true;
                                        anterior = 3;
                                    }
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                 break;
                            case SDLK_SPACE:
                                s_rect = loadTexture("cuerpo.png",s_rect);
                                start = true;
                                break;
                            default:
                                break;
                            }

                            //SDL_BlitSurface(CurrentSurface,NULL,screenSurface,NULL);
                            SDL_UpdateWindowSurface(window);

                        }
                    }
                }
                else
                {
                    s_rect = loadTexture("game over.png",s_rect);
                    scr = 0;
                    tail = 0;
                    update(s_rect,fruta);
                    for(int i=0;i<4;i++)
                    {
                        direccio[i] = false;
                    }
                    for(int i=0;i<tail;i++)
                    {
                        posicioCua[i].x = 0;
                        posicioCua[i].y = 0;
                    }
                    anterior = 5;
                    switch(corazones)
                    {
                    case 0:
                        corazones_t = IMG_LoadTexture(renderer,"corazones-3.png");
                        break;
                    case 1:
                        corazones_t = IMG_LoadTexture(renderer,"corazones-2.png");
                        break;
                    case 2:
                        corazones_t = IMG_LoadTexture(renderer,"corazones-1.png");
                        break;

                    }
                    startgame = timeGET();


                }
        }
    }

    return 0;
}

bool init ()
{
    bool yep = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL no se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        yep = false;
    }
    else
    {
        //Creamos la ventana
        window = SDL_CreateWindow("SNAKE", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("La ventana no se ha podido abrir! SDL_ERROR: %s\n", SDL_GetError());
            yep = false;
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("La imagen no se ha podido inicializar");
                yep = false;
            }
            else
            {
                if( TTF_Init() != 0)
                {
                    printf("Error no se ha podido inicializar TTF");
                    yep = false;
                }
                else
                {
                    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
                    if(renderer == NULL)
                    {
                        yep=false;
                        printf("error en inicializar el renderer");
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
                        tail_t = IMG_LoadTexture(renderer,"cola.png");
                        puntuacio = IMG_LoadTexture(renderer,"PUNTUACIO.png");
                        vidas_t = IMG_LoadTexture(renderer,"VIDAS.png");

                        for(int i=0;i<460;i++)
                        {
                            posicioCua[i].h = 20;
                            posicioCua[i].w = 20;
                        }

                    }

                }

            }
        }
    }

    return yep;
}



void close()
{
    //Destroy todo
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(aux);
    SDL_DestroyTexture(fruta_t);

    SDL_Quit();
}

