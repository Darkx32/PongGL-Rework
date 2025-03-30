#pragma once
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "rect.hpp"
#include "circle.hpp"
#include "global.hpp"
#include "UI.hpp"
#include "sound.hpp"

class Game
{
private:
    SDL_Window* window;
    SDL_GLContext context;

    // Objects in scene
    Rect bar;
    Rect bar2;
    Circle circle;

    // UI
    UI ui;

    // Sound
    Sound sound;

    Uint64 lastTime = 0.f;

    int upPoints = 0;
    int downPoints = 0;

public:
    Game() = default;
    ~Game();

    SDL_AppResult start();
    SDL_AppResult handleEvents(SDL_Event* events);
    SDL_AppResult updatePhysics();
    SDL_AppResult updateRender();

    float deltaTime = 0.f;
};