#pragma once
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include "rect.hpp"

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

Game::~Game()
{
    rect.close();

    SDL_GL_DestroyContext(this->context);
    SDL_DestroyWindow(this->window);
    SDL_Log("Successfully! Game is running okay!");
    SDL_Quit();
}

SDL_AppResult Game::start()
{
    SDL_AppResult result = SDL_APP_CONTINUE;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to init SDL3: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this->window = SDL_CreateWindow("PongGL - Rework", 360, 480, SDL_WINDOW_OPENGL);
    if (!this->window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    this->context = SDL_GL_CreateContext(this->window);
    if (!this->context)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to create OpenGL Context: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(1);

    result = rect.init(glm::vec2(0.0f), glm::vec2(20.f), glm::vec3(1.0f));
    if (result != SDL_APP_CONTINUE)
        return result;

    return result;
}

SDL_AppResult Game::handleEvents(SDL_Event* events)
{
    if (events->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::updatePhysics()
{
    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::updateRender()
{
    SDL_AppResult result = SDL_APP_CONTINUE;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    result = rect.render();
    if (result != SDL_APP_CONTINUE)
        return result;

    SDL_GL_SwapWindow(this->window);

    return result;
}