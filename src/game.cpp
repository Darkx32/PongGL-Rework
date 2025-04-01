#include "game.hpp"

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

    // Creating objects on game
    if ((result = bar.init(glm::vec2(WINDOW_SIZE[0] / 2.f - 30.f, 10.f), glm::vec2(60.f, 10.f), glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    if ((result = bar2.init(glm::vec2(WINDOW_SIZE[0] / 2.f - 30.f, WINDOW_SIZE[1] - 20.f), glm::vec2(60.f, 10.f), glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    if ((result = circle.init(glm::vec2(.0f), 10, glm::vec3(1.f))) != SDL_APP_CONTINUE)
        return result;

    this->circle.restart();

    // Starting User Interface
    if ((result = ui.init(this->window, this->context, &this->upPoints, &this->downPoints)) != SDL_APP_CONTINUE)
        return result;

    this->lastTime = SDL_GetTicks();

    // Start up audio
    if ((result = sound.init("assets/sounds/background.mp3", "assets/sounds/ball.mp3", "assets/sounds/win.mp3")) != SDL_APP_CONTINUE)
        return result;
    //this->sound.playMusicSound();

    return result;
}

SDL_AppResult Game::handleEvents(SDL_Event* events)
{
    SDL_AppResult result = SDL_APP_CONTINUE;
    auto state = SDL_GetKeyboardState(NULL);

    if (events->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;
    if (state[SDL_SCANCODE_RETURN] && !ui.hasStarted)
        ui.hasStarted = true;

    if (!ui.hasStarted)
        return result;

    if ((result = ui.processEvents(events)) != SDL_APP_CONTINUE)
        return result;

    if (state[SDL_SCANCODE_A] && (*bar.r_position).x > 20.f)
        bar.applyForce(glm::vec2(-5.0f, 0.0f));
    else if (state[SDL_SCANCODE_D] && (*bar.r_position).x + (*bar.r_scale).x < WINDOW_SIZE[0] - 20.f)
        bar.applyForce(glm::vec2(5.0f, 0.0f));

    if (state[SDL_SCANCODE_LEFT] && (*bar2.r_position).x > 20.f)
        bar2.applyForce(glm::vec2(-5.0f, 0.0f));
    else if (state[SDL_SCANCODE_RIGHT] && (*bar2.r_position).x + (*bar2.r_scale).x < WINDOW_SIZE[0] - 20.f)
        bar2.applyForce(glm::vec2(5.0f, 0.0f));

    return result;
}

SDL_AppResult Game::updatePhysics()
{
    if (!ui.hasStarted)
        return SDL_APP_CONTINUE;

    this->bar.updatePhysics();
    this->bar2.updatePhysics();

    if (this->bar.detectCollision(this->circle))
    {
        this->circle.solveCircleCollision(this->bar);
        this->sound.playCollisionBall(*this->circle.r_position);
    }
    else if (this->bar2.detectCollision(this->circle))
    {
        this->circle.solveCircleCollision(this->bar2);
        this->sound.playCollisionBall(*this->circle.r_position);
    }

    if ((*this->circle.r_position).x <= 0.0f)
    {
        this->circle.applyForce(this->circle.getAcceleration() * glm::vec2(-2.0f, 0.0f));
        this->sound.playCollisionBall(*this->circle.r_position);
    }
    if ((*circle.r_position).x + *this->circle.r_radius * 2.0f >= WINDOW_SIZE[0])
    {
        this->circle.applyForce(this->circle.getAcceleration() * glm::vec2(-2.0f, 0.0f));
        this->sound.playCollisionBall(*this->circle.r_position);
    }
        
    this->circle.updatePhysics();

    if (((*this->circle.r_position).y + *this->circle.r_radius) <= 0.0f)
    {
        this->circle.restart();
        this->downPoints++;
        this->ui.hasStarted = false;
        this->sound.playWin();
    } else if ((*this->circle.r_position).y >= WINDOW_SIZE[1])
    {
        this->circle.restart();
        this->upPoints++;
        this->ui.hasStarted = false;
        this->sound.playWin();
    }

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

    if ((result = ui.render(this->deltaTime)) != SDL_APP_CONTINUE)
        return result;

    Uint64 currentTime = SDL_GetTicks();
    this->deltaTime = (currentTime - this->lastTime) / 1000.f;
    this->lastTime = currentTime;

    SDL_GL_SwapWindow(this->window);
    this->sound.updateSwaps();

    return result;
}

Game::~Game()
{
    this->bar.close();
    this->bar2.close();
    this->circle.close();

    this->ui.shutdown();
    this->sound.close();

    SDL_GL_DestroyContext(this->context);
    SDL_DestroyWindow(this->window);
    SDL_Log("Successfully! Game is running okay!");
    SDL_Quit();
}