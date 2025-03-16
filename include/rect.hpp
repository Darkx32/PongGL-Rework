#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <shader.hpp>
#include <global.hpp>
#include <rigidbody.hpp>

class Rect : public Rigidbody
{
private:
    glm::vec2 position, scale;
    glm::vec3 color;

    GLuint VAO;
    Shader shader;

    char infoLog[512];

public:
    SDL_AppResult init(glm::vec2, glm::vec2, glm::vec3);
    SDL_AppResult render();
    void updatePhysics();
    void close();

};