#pragma once
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <SDL3/SDL.h>
#include "global.hpp"
#include <string>

class UI
{
private:
    Uint64 startTime;
    const int justTextFlags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    const char* startText = "Press ENTER to start game";

    int* upPoints;
    int* downPoints;

public:
    SDL_AppResult init(SDL_Window*, SDL_GLContext, int*, int*);
    SDL_AppResult processEvents(SDL_Event*);
    SDL_AppResult render(float&);
    void shutdown();

    bool hasStarted = false;
    bool showFPS = true;
};
