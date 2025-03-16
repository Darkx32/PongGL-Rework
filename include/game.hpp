#pragma once
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "rect.hpp"
#include "global.hpp"

class Game
{
private:
    SDL_Window* window;
    SDL_GLContext context;

    Rect rect;

public:
    Game() = default;
    ~Game();

    SDL_AppResult start();
    SDL_AppResult handleEvents(SDL_Event* events);
    SDL_AppResult updatePhysics();
    SDL_AppResult updateRender();
};