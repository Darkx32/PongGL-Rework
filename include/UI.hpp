#pragma once
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>

class UI
{
private:
    Uint64 startTime;

public:
    SDL_AppResult init(SDL_Window*, SDL_GLContext);
    SDL_AppResult processEvents(SDL_Event*);
    SDL_AppResult render(float&);
    void shutdown();
};
