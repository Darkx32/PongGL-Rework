#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "game.hpp"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_AppResult result = SDL_APP_CONTINUE;
    Game* game = new Game();
    result = game->start();
    if (result != SDL_APP_CONTINUE)
        return result;

    *appstate = game;

    return result;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* events)
{
    Game* game = static_cast<Game*>(appstate);
    return game->handleEvents(events);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_AppResult result = SDL_APP_CONTINUE;
    Game* game = static_cast<Game*>(appstate);

    result = game->updatePhysics();
    if (result != SDL_APP_CONTINUE)
        return result;

    result = game->updateRender();
    if (result != SDL_APP_CONTINUE)
        return result;

    if (game->deltaTime < TARGET_FPS)
        SDL_Delay(TARGET_FPS - game->deltaTime);

    return result;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    Game* game = static_cast<Game*>(appstate);

    delete game;
}