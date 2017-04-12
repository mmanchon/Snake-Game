#inculde"game.h"

game::game()
{
    window = NULL;
    Running = true;
    background = NULL;
    message = NULL;
    font = NULL;
    text = NULL;
    textColor.r=255;textColor.g=255;textColor.b=255;
    typing=0;
    data="";
}

int game::OnExecute()
{
    if(OnInit()==false)
    {
        return -1;
    }

    if(LoadContent() == false)
    {
        return -1
    }

    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }
        OnLoop();
        OnRender();
    }
    Cleanup();
    return 0;
}
