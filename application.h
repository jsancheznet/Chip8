#pragma once

#include <SDL.h>

struct application
{
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    b32 IsRunning;
};
