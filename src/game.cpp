#include "game.hpp"

Game::~Game()
{
    bar.close();
    bar2.close();
    circle.close();

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

    this->window = SDL_CreateWindow("PongGL - Rework", WINDOW_SIZE[0], WINDOW_SIZE[1], SDL_WINDOW_OPENGL);
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

    if ((result = bar.init(glm::vec2(WINDOW_SIZE[0] / 2.f, 10.f), glm::vec2(60.f, 10.f), glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    if ((result = bar2.init(glm::vec2(WINDOW_SIZE[0] / 2.f, WINDOW_SIZE[1] - 20.f), glm::vec2(60.f, 10.f), glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    if ((result = circle.init(glm::vec2(.0f), 10, glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    this->restartCircle();
    return result;
}

SDL_AppResult Game::handleEvents(SDL_Event* events)
{
    if (events->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    auto state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A] && (*bar.r_position).x > 20.f)
        bar.applyForce(glm::vec2(-5.0f, 0.0f));
    else if (state[SDL_SCANCODE_D] && (*bar.r_position).x + (*bar.r_scale).x < WINDOW_SIZE[0] - 20.f)
        bar.applyForce(glm::vec2(5.0f, 0.0f));

    if (state[SDL_SCANCODE_LEFT] && (*bar2.r_position).x > 20.f)
        bar2.applyForce(glm::vec2(-5.0f, 0.0f));
    else if (state[SDL_SCANCODE_RIGHT] && (*bar2.r_position).x + (*bar2.r_scale).x < WINDOW_SIZE[0] - 20.f)
        bar2.applyForce(glm::vec2(5.0f, 0.0f));

    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::updatePhysics()
{
    this->bar.updatePhysics();
    this->bar2.updatePhysics();

    if (this->bar.detectCollision(this->circle))
    {
        this->circle.solveCircleCollision(this->bar);
    }
    else if (this->bar2.detectCollision(this->circle))
    {
        this->circle.solveCircleCollision(this->bar2);
    }

    if ((*this->circle.r_position).x <= 0.0f)
        this->circle.applyForce(this->circle.getAcceleration() * glm::vec2(-2.0f, 0.0f));
    if ((*circle.r_position).x + *this->circle.r_radius * 2.0f >= WINDOW_SIZE[0])
        this->circle.applyForce(this->circle.getAcceleration() * glm::vec2(-2.0f, 0.0f));
        
    this->circle.updatePhysics();

    if ((*this->circle.r_position).y >= WINDOW_SIZE[1] || ((*this->circle.r_position).y + *this->circle.r_radius) <= 0.0f)
        this->restartCircle();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Game::updateRender()
{
    SDL_AppResult result = SDL_APP_CONTINUE;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if ((result = bar.render()) != SDL_APP_CONTINUE)
        return result;

    if ((result = bar2.render()) != SDL_APP_CONTINUE)
        return result;

    if ((result = circle.render()) != SDL_APP_CONTINUE)
        return result;

    SDL_GL_SwapWindow(this->window);

    return result;
}

void Game::restartCircle()
{
    *this->circle.r_position = glm::vec2(WINDOW_SIZE[0] / 2.f, WINDOW_SIZE[1] / 2.f);
    this->circle.applyForce(-this->circle.getAcceleration());
    
    float random_force = 5.0f;
    int number = rand() % 2;
    random_force *= number ? -1.0f : 1.0f;
    circle.applyForce(glm::vec2(5.0f, random_force));
}
