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

SDL_AppResult Shader::init(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    int exception = (std::ifstream::failbit | std::ifstream::badbit);

    vShaderFile.exceptions(exception);
    fShaderFile.exceptions(exception);

    try {
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to open shader files");
        return SDL_APP_FAILURE;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to compile vertex shader: %s", infoLog);
        return SDL_APP_FAILURE;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to compile fragment shader: %s", infoLog);
        return SDL_APP_FAILURE;
    }

    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);

    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to attach and link shaders in program: %s", infoLog);
        return SDL_APP_FAILURE;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return SDL_APP_CONTINUE;
}

void Shader::close()
{
    glDeleteProgram(this->program);
}
