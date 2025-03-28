#pragma once
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>
#include "global.hpp"

class UI
{
private:
    Uint64 startTime;
    const char* startText = "Press ENTER to start game";

public:
    SDL_AppResult init(SDL_Window*, SDL_GLContext);
    SDL_AppResult processEvents(SDL_Event*);
    SDL_AppResult render(float&);
    void shutdown();

    bool hasStarted = false;
    bool showFPS = true;
};
