#pragma once
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <fstream>
#include <sstream>

class Shader
{
public:
    GLuint program;

    SDL_AppResult init(const char*, const char*);
    void close();
};