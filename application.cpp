#pragma once

#include "application.h"

void HandleApplicationArguments(i32 Argc, char **Argv)
{
    if(Argc < 2)
    {
        std::cout << "Error, please add a chip8 file as parameter" << std::endl;
        std::cout << "Example: chip8.exe my_rom.ch8" << std::endl;
        exit(-1);
    }

    Argv;
}

void CreateApplication(application *Application, char *WindowTitle, i32 Width, i32 Height)
{
    Assert(Application);

    Application->IsRunning = true;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    Application->Window   = SDL_CreateWindow(WindowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_ALLOW_HIGHDPI);
    Application->Renderer = SDL_CreateRenderer(Application->Window, -1, SDL_RENDERER_ACCELERATED);
}

void HandleInput(application *Application)
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        ImGui_ImplSDL2_ProcessEvent(&Event);

        switch(Event.type)
        {
            case SDL_QUIT:
            {
                Application->IsRunning = false;
                break;
            }

            case SDL_KEYDOWN:
            {
                if(Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    Application->IsRunning = false;
                }
                break;
            }
            case SDL_KEYUP:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }
}
